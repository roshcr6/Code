#include <stdio.h>
#include <unistd.h>

int main() {
    char *args[] = {"./program2", NULL};
    execvp(args[0], args);
    return 0;
}
