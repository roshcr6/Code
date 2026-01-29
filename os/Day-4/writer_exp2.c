#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = ftok("shmfile", 75);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    char *str = (char*) shmat(shmid, NULL, 0);

    printf("Enter a string: ");
    fgets(str, 1024, stdin);

    printf("String written to shared memory\n");

    shmdt(str);
    return 0;
}
