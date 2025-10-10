#include <stdio.h>

int main() {
    int n, num, count = 0;
    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter number to count: ");
    scanf("%d", &num);

    for (int i = 0; i < n; i++)
        if (arr[i] == num)
            count++;

    printf("Number %d occurs %d times in the array.", num, count);
    return 0;
}

