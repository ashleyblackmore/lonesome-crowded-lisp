#include <stdio.h>
#include <stdlib.h>

/* if we are compiling on Windows, compile these functions */
#ifdef _WIN32

#include <string.h>

static char buffer[2048];

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

#include <editline/readline.h>
#include <editline/history.h>

#endif

int main(int argc, char** argv) {
    puts("Lonesome Crowded Lisp 0.0.0.0.1");
    puts("Press Ctrl+c to exit\n");

    while (1) {
        /* now in either case, readline will be defined */
        char* input = readline("(づ￣ ³￣)づ ");
        add_history(input);

        /* echo input back to user */
        printf("Three inch horses, %s\n", input);
        free(input);
    }

    return 0;
}
