#include <stdio.h>

/* Declare a static buffer for user input (max size 2048 chars) */
static char input[2048];

int main(int argc, char** argv) {
    /* version and exit info */
    puts("Lonesome Crowded Lisp 0.0.0.0.1");
    puts("Press Ctrl+c to exit\n");

    while (1) {
        /* Output a prompt */
        fputs("(づ￣ ³￣)づ ", stdout);

        /* Read a line of user input */
        fgets(input, 2048, stdin);

        /* Echo input back to user */
        printf("Three inch horses, %s", input);
    }

    return 0;
}
