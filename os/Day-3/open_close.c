#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("test.txt", O_RDONLY);

    if(fd < 0) {
        printf("Error opening file\n");
        return 1;
    }

    printf("File opened with fd = %d\n", fd);
    close(fd);
    printf("File closed\n");

    return 0;
}
