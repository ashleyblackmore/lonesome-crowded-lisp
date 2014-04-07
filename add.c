#include <stdio.h>

void hallo(int x);

int main(int argc, char** argv) {
    hallo(5000000);
    return 0;
}

void hallo(int x) {
    for (int i = 0; i < x; i++) {
        printf("%d Hallo, Welt!\n", i);
    }
}
