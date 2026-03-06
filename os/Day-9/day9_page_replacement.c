#include <stdio.h>
#include <stdlib.h>

void fcfs(int req[], int n, int head)
{
    int total = 0;
    int cur = head;

    printf("\nFCFS Order: %d ", cur);

    for(int i=0;i<n;i++)
    {
        total += abs(req[i] - cur);
        cur = req[i];
        printf("-> %d ", cur);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

void scan(int req[], int n, int head, int size)
{
    int total = 0;
    int cur = head;
    int temp[100], k = 0;

    for(int i=0;i<n;i++)
        temp[k++] = req[i];

    temp[k++] = 0;
    temp[k++] = head;

    for(int i=0;i<k-1;i++)
        for(int j=0;j<k-i-1;j++)
            if(temp[j] > temp[j+1])
            {
                int t = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = t;
            }

    int pos;
    for(int i=0;i<k;i++)
        if(temp[i] == head)
            pos = i;

    printf("\nSCAN Order: %d ", cur);

    for(int i=pos-1;i>=0;i--)
    {
        total += abs(cur - temp[i]);
        cur = temp[i];
        printf("-> %d ", cur);
    }

    cur = 0;

    for(int i=pos+1;i<k;i++)
    {
        total += abs(cur - temp[i]);
        cur = temp[i];
        printf("-> %d ", cur);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

void cscan(int req[], int n, int head, int size)
{
    int total = 0;
    int cur = head;
    int temp[100], k = 0;

    for(int i=0;i<n;i++)
        temp[k++] = req[i];

    temp[k++] = 0;
    temp[k++] = size-1;
    temp[k++] = head;

    for(int i=0;i<k-1;i++)
        for(int j=0;j<k-i-1;j++)
            if(temp[j] > temp[j+1])
            {
                int t = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = t;
            }

    int pos;
    for(int i=0;i<k;i++)
        if(temp[i] == head)
            pos = i;

    printf("\nC-SCAN Order: %d ", cur);

    for(int i=pos+1;i<k;i++)
    {
        total += abs(cur - temp[i]);
        cur = temp[i];
        printf("-> %d ", cur);
    }

    cur = 0;

    for(int i=0;i<pos;i++)
    {
        total += abs(cur - temp[i]);
        cur = temp[i];
        printf("-> %d ", cur);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

int main()
{
    int n, head, size;

    printf("Enter number of requests: ");
    scanf("%d",&n);

    int req[n];

    printf("Enter disk requests:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&req[i]);

    printf("Enter initial head position: ");
    scanf("%d",&head);

    printf("Enter disk size: ");
    scanf("%d",&size);

    fcfs(req,n,head);
    scan(req,n,head,size);
    cscan(req,n,head,size);

    return 0;
}
