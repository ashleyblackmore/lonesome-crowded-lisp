#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/history.h>

int main(int argc, char** argv) {
    /* version and exit info */
    puts("Lonesome Crowded Lisp 0.0.0.0.1");
    puts("Press Ctrl+c to exit\n");

    /* looooooop */
    while (1) {
        /* output a prompt */
        char* input = readline("(づ￣ ³￣)づ ");
        add_history(input);

        /* echo input back to user */
        printf("Three inch horses, %s\n", input);

        /* free retrieved input */
        free(input);
    }

    return 0;
}
