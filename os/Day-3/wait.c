#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    if(fork() == 0) {
        printf("Child exiting\n");
    } else {
        wait(NULL);
        printf("Parent resumed\n");
    }
    return 0;
}
