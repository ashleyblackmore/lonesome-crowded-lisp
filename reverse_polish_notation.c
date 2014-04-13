#include "mpc.h"

/* if we are compiling on Windows, compile these functions */
#ifdef _WIN32

static char buffer[2048];

void add_history(char* unused);
long eval_op(long x, char* op, long y);
long eval(mpc_ast_t* t);

/* fake readline function */
char* readline(char* prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer)+1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy)-1] = '\0';
    return cpy;
}

/* fake add_history function */
void add_history(char* unused) {}

/* otherwise, include the editline headers */

#else

#include <editline/readline.h>
#include <editline/history.h>

#endif

long eval_op(long x, char* op, long y) {
    if (strcmp(op, "+") == 0) { return x + y; }
    if (strcmp(op, "-") == 0) { return x - y; }
    if (strcmp(op, "*") == 0) { return x * y; }
    if (strcmp(op, "/") == 0) { return x / y; }
    return 0;
}

long eval(mpc_ast_t* t) {
    /* if tagged as a number, return directly, otherwise expr */
    if (strstr(t->tag, "number")) { return atoi(t->contents); }

    /* the operator is always the second child */
    char* op = t->children[1]->contents;

    /* we store the third child in `x` */
    long x = eval(t->children[2]);

    /* iterate remaining children, combining using our operator */
    int i = 3;
    while (strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }

    return x;
}

int main(int argc, char** argv) {

    mpc_parser_t* Number    = mpc_new("number");
    mpc_parser_t* Operator  = mpc_new("operator");
    mpc_parser_t* Expr      = mpc_new("expr");
    mpc_parser_t* Lclisp    = mpc_new("lclisp");


    mpca_lang(MPC_LANG_DEFAULT,
        "                                                   \
        number   : /-?[0-9]+/ ;                             \
        operator : '+' | '-' | '*' | '/' ;                  \
        expr     : <number> | '(' <operator> <expr>+ ')' ;  \
        lclisp   : /^/ <operator> <expr>+ /$/ ;             \
        ",
        Number, Operator, Expr, Lclisp);

    puts("Lonesome Crowded Lisp 0.0.0.0.2");
    puts("Press Ctrl+c to exit\n");

    while (1) {

        char* input = readline("(づ￣ ³￣)づ ");
        add_history(input);

        /* attempt parsing user input */
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lclisp, &r)) {
            /* on success, print the AST */
            long result = eval(r.output);
            printf("%li\n", result);
            mpc_ast_delete(r.output);
        } else {
            /* else, print the error */
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);

    }

    /* undefine and delete parsers */
    mpc_cleanup(4, Number, Operator, Expr, Lclisp);

    return 0;
}
