#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666);

    int *data = (int*) shmat(shmid, NULL, 0);

    int nCr = data[0] / (data[1] * data[2]);
    printf("nCr value = %d\n", nCr);

    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
