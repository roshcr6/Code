#include <stdio.h>

struct process {
    int pid, at, bt, pr;
    int ct, tat, wt;
};

void printGantt(int gp[], int gt[], int gc) {
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gc; i++)
        printf(" P%d |", gp[i]);
    printf("\n");
    for (int i = 0; i < gc; i++)
        printf("%-5d", gt[i]);
    printf("%d\n", gt[gc]);
}

void fcfs(struct process p[], int n) {
    int time = 0, gp[50], gt[50], gc = 0;

    for(int i = 0; i < n; i++)
        p[i].ct = p[i].tat = p[i].wt = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        gp[gc] = p[i].pid;
        gt[gc++] = time;

        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
    gt[gc] = time;

    printGantt(gp, gt, gc);

    printf("\nPID AT BT CT TAT WT\n");
    for (int i = 0; i < n; i++)
        printf("P%d  %d  %d  %d  %d  %d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
}

void sjf(struct process p[], int n) {
    int time = 0, completed = 0;
    int done[n], gp[50], gt[50], gc = 0;

    for (int i = 0; i < n; i++) {
        done[i] = 0;
        p[i].ct = p[i].tat = p[i].wt = 0;
    }

    while (completed < n) {
        int idx = -1, min = 9999;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].bt < min) {
                min = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        gp[gc] = p[idx].pid;
        gt[gc++] = time;

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        done[idx] = 1;
        completed++;
    }
    gt[gc] = time;

    printGantt(gp, gt, gc);

    printf("\nPID AT BT CT TAT WT\n");
    for (int i = 0; i < n; i++)
        printf("P%d  %d  %d  %d  %d  %d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
}

void roundRobin(struct process p[], int n) {
    int tq, rt[n], time = 0, completed = 0;
    int gp[50], gt[50], gc = 0;

    for (int i = 0; i < n; i++) {
        rt[i] = p[i].bt;
        p[i].ct = p[i].tat = p[i].wt = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    while (completed < n) {
        int executed = 0;

        for (int i = 0; i < n; i++) {
            if (rt[i] > 0 && p[i].at <= time) {
                executed = 1;

                gp[gc] = p[i].pid;
                gt[gc++] = time;

                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    rt[i] = 0;
                    p[i].ct = time;
                    completed++;
                }
            }
        }
        if (!executed)
            time++;
    }
    gt[gc] = time;

    printGantt(gp, gt, gc);

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    printf("\nPID AT BT CT TAT WT\n");
    for (int i = 0; i < n; i++)
        printf("P%d  %d  %d  %d  %d  %d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
}

void priority(struct process p[], int n) {
    int time = 0, completed = 0;
    int done[n], gp[50], gt[50], gc = 0;

    for (int i = 0; i < n; i++) {
        done[i] = 0;
        p[i].ct = p[i].tat = p[i].wt = 0;
    }

    while (completed < n) {
        int idx = -1, high = 9999;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].pr < high) {
                high = p[i].pr;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        gp[gc] = p[idx].pid;
        gt[gc++] = time;

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        done[idx] = 1;
        completed++;
    }
    gt[gc] = time;

    printGantt(gp, gt, gc);

    printf("\nPID AT BT PR CT TAT WT\n");
    for (int i = 0; i < n; i++)
        printf("P%d  %d  %d  %d  %d  %d  %d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
}

int main() {
    int choice, n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT, BT and Priority for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
    }

    do {
        printf("\n--- CPU Scheduling Menu ---\n");
        printf("1. FCFS\n");
        printf("2. SJF (Non-Preemptive)\n");
        printf("3. Round Robin\n");
        printf("4. Priority (Non-Preemptive)\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: fcfs(p, n); break;
            case 2: sjf(p, n); break;
            case 3: roundRobin(p, n); break;
            case 4: priority(p, n); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice\n");
        }
    } while (choice != 5);

    return 0;
}
