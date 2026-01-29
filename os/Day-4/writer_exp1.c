#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int factorial(int x) {
    int f = 1;
    for(int i = 1; i <= x; i++)
        f *= i;
    return f;
}

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    int *data = (int*) shmat(shmid, NULL, 0);

    int n, r;
    printf("Enter n and r: ");
    scanf("%d %d", &n, &r);

    data[0] = factorial(n);
    data[1] = factorial(r);
    data[2] = factorial(n - r);

    printf("Factorials written to shared memory\n");

    shmdt(data);
    return 0;
}
