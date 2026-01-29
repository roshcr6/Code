#include <stdio.h>

int AT[10], BT[10], PR[10];
int CT[10], TAT[10], WT[10];
int n;

/* Common function to print table */
void printTable() {
    float avgTAT = 0, avgWT = 0;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i];
        WT[i]  = TAT[i] - BT[i];
        avgTAT += TAT[i];
        avgWT  += WT[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, AT[i], BT[i], CT[i], TAT[i], WT[i]);
    }

    printf("Average Turnaround Time = %.2f\n", avgTAT / n);
    printf("Average Waiting Time    = %.2f\n", avgWT / n);
}

/* FCFS Scheduling */
void fcfs() {
    int time = 0;

    for(int i = 0; i < n; i++) {
        if(time < AT[i])
            time = AT[i];
        time += BT[i];
        CT[i] = time;
    }
    printTable();
}

/* SJF (Non-Preemptive) */
void sjf() {
    int done[10] = {0};
    int time = 0, completed = 0;

    while(completed < n) {
        int idx = -1, minBT = 9999;

        for(int i = 0; i < n; i++) {
            if(AT[i] <= time && !done[i] && BT[i] < minBT) {
                minBT = BT[i];
                idx = i;
            }
        }

        if(idx == -1) {
            time++;
            continue;
        }

        time += BT[idx];
        CT[idx] = time;
        done[idx] = 1;
        completed++;
    }
    printTable();
}

/* Priority Scheduling (Non-Preemptive) */
void priority() {
    int done[10] = {0};
    int time = 0, completed = 0;

    while(completed < n) {
        int idx = -1, minPR = 9999;

        for(int i = 0; i < n; i++) {
            if(AT[i] <= time && !done[i] && PR[i] < minPR) {
                minPR = PR[i];
                idx = i;
            }
        }

        if(idx == -1) {
            time++;
            continue;
        }

        time += BT[idx];
        CT[idx] = time;
        done[idx] = 1;
        completed++;
    }
    printTable();
}

/* Round Robin Scheduling */
void roundRobin() {
    int tq, rem[10];
    int time = 0, completed = 0;

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    for(int i = 0; i < n; i++)
        rem[i] = BT[i];

    while(completed < n) {
        for(int i = 0; i < n; i++) {
            if(rem[i] > 0 && AT[i] <= time) {
                if(rem[i] > tq) {
                    time += tq;
                    rem[i] -= tq;
                } else {
                    time += rem[i];
                    rem[i] = 0;
                    CT[i] = time;
                    completed++;
                }
            }
        }
    }
    printTable();
}

int main() {
    int choice;

    do {
        printf("\n--- CPU Scheduling Menu ---\n1. FCFS\n2. SJF (Non-Preemptive)\n3. Round Robin (Pre-emptive)\n4. Priority (Non-Preemptive)\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        if(choice >= 1 && choice <= 4) {
            printf("Enter number of processes: ");
            scanf("%d", &n);

            for(int i = 0; i < n; i++) {
                if(choice == 4) {
                    printf("Enter AT, BT and Priority for P%d: ", i+1);
                    scanf("%d %d %d", &AT[i], &BT[i], &PR[i]);
                } else {
                    printf("Enter AT and BT for P%d: ", i+1);
                    scanf("%d %d", &AT[i], &BT[i]);
                }
            }
        }

        switch(choice) {
            case 1: fcfs(); break;
            case 2: sjf(); break;
            case 3: roundRobin(); break;
            case 4: priority(); break;
            case 5: printf("Exiting program\n"); break;
            default: printf("Invalid choice\n");
        }

    } while(choice != 5);

    return 0;
}
