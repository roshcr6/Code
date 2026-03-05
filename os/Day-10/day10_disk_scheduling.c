#include <stdio.h>
#include <stdlib.h>

#define MAX 50

void sort(int a[], int n)
{
    int i,j,temp;
    for(i=0;i<n-1;i++)
        for(j=0;j<n-i-1;j++)
            if(a[j]>a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
}

void fcfs(int req[], int n, int head)
{
    int seek=0,i;

    printf("\nFCFS Order: %d ",head);

    for(i=0;i<n;i++)
    {
        seek+=abs(req[i]-head);
        head=req[i];
        printf("-> %d ",head);
    }

    printf("\nTotal Head Movement = %d\n",seek);
}

void scan(int req[], int n, int head, int disk)
{
    int left[MAX],right[MAX];
    int l=0,r=0,i,seek=0;

    for(i=0;i<n;i++)
        if(req[i]<head)
            left[l++]=req[i];
        else
            right[r++]=req[i];

    sort(left,l);
    sort(right,r);

    printf("\nSCAN Order: %d ",head);

    for(i=0;i<r;i++)
    {
        seek+=abs(head-right[i]);
        head=right[i];
        printf("-> %d ",head);
    }

    seek+=abs(head-(disk-1));
    head=disk-1;
    printf("-> %d ",head);

    for(i=l-1;i>=0;i--)
    {
        seek+=abs(head-left[i]);
        head=left[i];
        printf("-> %d ",head);
    }

    printf("\nTotal Head Movement = %d\n",seek);
}

void cscan(int req[], int n, int head, int disk)
{
    int left[MAX],right[MAX];
    int l=0,r=0,i,seek=0;

    for(i=0;i<n;i++)
        if(req[i]<head)
            left[l++]=req[i];
        else
            right[r++]=req[i];

    sort(left,l);
    sort(right,r);

    printf("\nC-SCAN Order: %d ",head);

    for(i=0;i<r;i++)
    {
        seek+=abs(head-right[i]);
        head=right[i];
        printf("-> %d ",head);
    }

    seek+=abs(head-(disk-1));
    head=disk-1;
    printf("-> %d ",head);

    seek+=disk-1;
    head=0;
    printf("-> %d ",head);

    for(i=0;i<l;i++)
    {
        seek+=abs(head-left[i]);
        head=left[i];
        printf("-> %d ",head);
    }

    printf("\nTotal Head Movement = %d\n",seek);
}

int main()
{
    int req[MAX],n,head,disk,i;

    printf("Enter number of requests: ");
    scanf("%d",&n);

    printf("Enter requests:\n");
    for(i=0;i<n;i++)
        scanf("%d",&req[i]);

    printf("Enter initial head position: ");
    scanf("%d",&head);

    printf("Enter disk size: ");
    scanf("%d",&disk);

    fcfs(req,n,head);
    scan(req,n,head,disk);
    cscan(req,n,head,disk);

    return 0;
}
