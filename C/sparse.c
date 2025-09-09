#include <stdio.h>
#define MAX 100

int sparse1[MAX][3], sparse2[MAX][3], result[MAX][3];

// Function to convert full matrix to sparse form
void convertToSparse(int matrix[10][10], int rows, int cols, int sparse[MAX][3]) {
    int k = 1;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (matrix[i][j] != 0) {
                sparse[k][0] = i;
                sparse[k][1] = j;
                sparse[k][2] = matrix[i][j];
                k++;
            }
    sparse[0][0] = rows;
    sparse[0][1] = cols;
    sparse[0][2] = k - 1;
}

// Display matrix in 2D form
void displayMatrixFromSparse(int sparse[MAX][3]) {
    int mat[10][10] = {0};
    int rows = sparse[0][0];
    int cols = sparse[0][1];
    int terms = sparse[0][2];

    for (int i = 1; i <= terms; i++)
        mat[sparse[i][0]][sparse[i][1]] = sparse[i][2];

    printf("Matrix (%dx%d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%3d ", mat[i][j]);
        printf("\n");
    }
}

// Display sparse triplet
void displaySparse(int sparse[MAX][3]) {
    int n = sparse[0][2];
    printf("Row Col Val\n");
    for (int i = 0; i <= n; i++)
        printf("%3d %3d %3d\n", sparse[i][0], sparse[i][1], sparse[i][2]);
}

// Read matrix from user
void readMatrix(int mat[10][10], int *rows, int *cols) {
    printf("Enter number of rows and columns: \n");
    scanf("%d%d", rows, cols);
    printf("Enter elements row-wise:\n");
    for (int i = 0; i < *rows; i++)
        for (int j = 0; j < *cols; j++)
            scanf("%d", &mat[i][j]);
}

// Add two sparse matrices
void addSparse(int A[MAX][3], int B[MAX][3], int res[MAX][3]) {
    if (A[0][0] != B[0][0] || A[0][1] != B[0][1]) {
        printf("Addition not possible. Dimensions mismatch.\n");
        return;
    }

    int i = 1, j = 1, k = 1;
    int n1 = A[0][2], n2 = B[0][2];

    res[0][0] = A[0][0];
    res[0][1] = A[0][1];

    while (i <= n1 && j <= n2) {
        if (A[i][0] < B[j][0] || (A[i][0] == B[j][0] && A[i][1] < B[j][1])) {
            res[k][0] = A[i][0];
            res[k][1] = A[i][1];
            res[k][2] = A[i][2];
            i++; k++;
        }
        else if (A[i][0] > B[j][0] || (A[i][0] == B[j][0] && A[i][1] > B[j][1])) {
            res[k][0] = B[j][0];
            res[k][1] = B[j][1];
            res[k][2] = B[j][2];
            j++; k++;
        }
        else {
            int sum = A[i][2] + B[j][2];
            if (sum != 0) {
                res[k][0] = A[i][0];
                res[k][1] = A[i][1];
                res[k][2] = sum;
                k++;
            }
            i++; j++;
        }
    }

    while (i <= n1) {
        res[k][0] = A[i][0];
        res[k][1] = A[i][1];
        res[k][2] = A[i][2];
        i++; k++;
    }

    while (j <= n2) {
        res[k][0] = B[j][0];
        res[k][1] = B[j][1];
        res[k][2] = B[j][2];
        j++; k++;
    }

    res[0][2] = k - 1;
}

// Transpose sparse matrix
void transposeSparse(int A[MAX][3], int res[MAX][3]) {
    int n = A[0][2];
    res[0][0] = A[0][1]; 
    res[0][1] = A[0][0]; 
    res[0][2] = n;

    int k = 1;
    for (int col = 0; col < A[0][1]; col++) {
        for (int i = 1; i <= n; i++) {
            if (A[i][1] == col) {
                res[k][0] = A[i][1];
                res[k][1] = A[i][0];
                res[k][2] = A[i][2];
                k++;
            }
        }
    }
}

int main() {
    int choice;
    int mat1[10][10], mat2[10][10];
    int r1, c1, r2, c2;

    while (1) {
        printf("\n--- Sparse Matrix Operations ---\n");
        printf("1. Add Two Matrices\n");
        printf("2. Transpose a Matrix\n");
        printf("3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter First Matrix:\n");
                readMatrix(mat1, &r1, &c1);
                convertToSparse(mat1, r1, c1, sparse1);

                printf("\nEnter Second Matrix:\n");
                readMatrix(mat2, &r2, &c2);
                convertToSparse(mat2, r2, c2, sparse2);

                printf("\nOriginal Matrix 1:\n");
                displayMatrixFromSparse(sparse1);

                printf("\nOriginal Matrix 2:\n");
                displayMatrixFromSparse(sparse2);

                addSparse(sparse1, sparse2, result);

                printf("\nSparse Matrix (Addition Result):\n");
                displaySparse(result);

                printf("\nResultant Matrix (2D Form):\n");
                displayMatrixFromSparse(result);
                break;

            case 2:
                printf("\nEnter Matrix to Transpose:\n");
                readMatrix(mat1, &r1, &c1);
                convertToSparse(mat1, r1, c1, sparse1);

                printf("\nOriginal Matrix:\n");
                displayMatrixFromSparse(sparse1);

                transposeSparse(sparse1, result);

                printf("\nSparse Matrix (Transpose):\n");
                displaySparse(result);

                printf("\nTransposed Matrix (2D Form):\n");
                displayMatrixFromSparse(result);
                break;

            case 3:
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

