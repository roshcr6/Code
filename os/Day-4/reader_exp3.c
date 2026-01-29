#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = ftok("shmfile", 85);
    int shmid = shmget(key, 1024, 0666);

    int *num = (int*) shmat(shmid, NULL, 0);

    int n = *num, rev = 0, temp = n;

    while(temp > 0) {
        rev = rev * 10 + temp % 10;
        temp /= 10;
    }

    printf("Reverse = %d\n", rev);

    if(n == rev)
        printf("Palindrome Number\n");
    else
        printf("Not a Palindrome Number\n");

    shmdt(num);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
