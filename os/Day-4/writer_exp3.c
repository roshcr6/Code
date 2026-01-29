#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = ftok("shmfile", 85);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    int *num = (int*) shmat(shmid, NULL, 0);

    printf("Enter a number: ");
    scanf("%d", num);

    printf("Number written to shared memory\n");

    shmdt(num);
    return 0;
}

