#include <stdio.h>

void rotateRight(int arr[], int n, int k) {
    k = k % n; // handle cases when k > n
    int temp[n];

    for (int i = 0; i < n; i++)
        temp[(i + k) % n] = arr[i];

    for (int i = 0; i < n; i++)
        arr[i] = temp[i];
}

int main() {
    int n, k;
    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter rotation count k: ");
    scanf("%d", &k);

    rotateRight(arr, n, k);

    printf("Array after rotating %d positions to the right:\n", k);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    return 0;
}

