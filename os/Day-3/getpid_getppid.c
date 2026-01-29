#include <stdio.h>
#include <unistd.h>

int main() {
    if(fork() == 0) {
        printf("Child PID  = %d\n", getpid());
        printf("Parent PID = %d\n", getppid());
    }
    return 0;
}
