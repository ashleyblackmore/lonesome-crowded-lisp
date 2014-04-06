#include <stdio.h>

int add_together(int x, int y);

int main(int argc, char** argv) {
    add_together(2, 2);
    return 0;
}

int add_together(int x, int y) {
    int result = x + y;
    puts(result);
    return result;
}
