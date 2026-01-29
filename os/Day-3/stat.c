#include <stdio.h>
#include <sys/stat.h>

int main() {
    struct stat s;

    stat("test.txt", &s);

    printf("Inode Number : %ld\n", s.st_ino);
    printf("File Size    : %ld bytes\n", s.st_size);

    return 0;
}
