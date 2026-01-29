#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    if(fork() == 0) {
        printf("Child Process\n");
        exit(0);
    } else {
        printf("Parent Process\n");
    }
    return 0;
}
