#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <ctype.h>

int main() {
    key_t key = ftok("shmfile", 75);
    int shmid = shmget(key, 1024, 0666);

    char *str = (char*) shmat(shmid, NULL, 0);

    int vowels = 0, digits = 0, symbols = 0;

    for(int i = 0; str[i] != '\0'; i++) {
        char ch = tolower(str[i]);

        if(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u')
            vowels++;
        else if(isdigit(ch))
            digits++;
        else if(!isalpha(ch) && !isspace(ch))
            symbols++;
    }

    printf("Vowels: %d\n", vowels);
    printf("Digits: %d\n", digits);
    printf("Symbols: %d\n", symbols);

    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
