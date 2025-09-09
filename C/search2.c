#include <stdio.h>

int linear_search(int a[], int n, int x, int index) {
    if (index >= n) return -1; 
    if (a[index] == x) return index;
    return linear_search(a, n, x, index + 1); 
}

int binary_search(int a[], int left, int right, int x) {
    if (left > right) return -1;
    int mid = left + (right - left) / 2;
    if (a[mid] == x) return mid;
    if (a[mid] < x) return binary_search(a, mid + 1, right, x);
    return binary_search(a, left, mid - 1, x);
}

void sort(int a[], int n) {
    if (n == 1) return;
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            int temp = a[i];
            a[i] = a[i + 1];
            a[i + 1] = temp;
        }
    }
    sort(a, n - 1);
}

void print_array(int a[], int index, int n) {
    if (index >= n) {
        printf("\n");
        return;
    }
    printf("%d ", a[index]);
    print_array(a, index + 1, n);
}

void menu(int a[], int size, int sorted) {
    int choice, x, result;
    printf("\n--MENU--\n");

    printf("\n1. Linear search\n");
    printf("2. Binary search\n");
    printf("3. Print array\n");
    printf("4. Quit\n");
    printf("Choose: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Number to search: ");
            scanf("%d", &x);
            result = linear_search(a, size, x, 0);
            if (result == -1)
                printf("Not found\n");
            else
                printf("Found at position %d\n", result + 1);
            break;

        case 2:
            if (!sorted) {
                sort(a, size);
                sorted = 1;
                printf("Note: Array is being sorted...\n");
            }
            printf("Sorted Array: ");
            print_array(a, 0, size);
            printf("Number to search: ");
            scanf("%d", &x);
            result = binary_search(a, 0, size - 1, x);
            if (result == -1)
                printf("Not found\n");
            else
                printf("Found at position %d\n", result + 1);
            break;

        case 3:
            printf("Array: ");
            print_array(a, 0, size);
            break;

        case 4:
            return;  

        default:
            printf("Invalid choice!\n");
    }

    menu(a, size, sorted);  
}


void read_array(int a[], int index, int n) {
    if (index == n) return;
    scanf("%d", &a[index]);
    read_array(a, index + 1, n);
}

int main() {
    int size, a[100];
    printf("Enter array size (<100): ");
    scanf("%d", &size);
    printf("Enter %d numbers: ", size);
    read_array(a, 0, size);  
    menu(a, size, 0);        
    return 0;
}

