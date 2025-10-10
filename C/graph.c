#include <stdio.h>
#define MAX 10

int adj[MAX][MAX], n;
int visited[MAX];

void createGraph() {
    int i, j;
    printf("\nEnter number of vertices: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix (%d x %d):\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }
}


void DFSUtil(int v) {
    int i;
    printf("%d ", v);
    visited[v] = 1;
    for (i = 0; i < n; i++) {
        if (adj[v][i] && !visited[i]) {
            DFSUtil(i);
        }
    }
}


void DFS() {
    int i, start;
    for (i = 0; i < n; i++)
        visited[i] = 0;
    printf("Enter starting vertex for DFS: ");
    scanf("%d", &start);
    printf("DFS Traversal: ");
    DFSUtil(start);
    printf("\n");
}


void BFS() {
    int i, start, front = 0, rear = -1;
    int queue[MAX];
    for (i = 0; i < n; i++)
        visited[i] = 0;
    printf("Enter starting vertex for BFS: ");
    scanf("%d", &start);
    queue[++rear] = start;
    visited[start] = 1;
    printf("BFS Traversal: ");
    while (front <= rear) {
        int v = queue[front++];
        printf("%d ", v);
        for (i = 0; i < n; i++) {
            if (adj[v][i] && !visited[i]) {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}


void display() {
    int i, j;
    printf("\nAdjacency Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%d ", adj[i][j]);
        printf("\n");
    }

    printf("\nAdjacency List:\n");
    for (i = 0; i < n; i++) {
        printf("%d -> ", i);
        for (j = 0; j < n; j++) {
            if (adj[i][j])
                printf("%d ", j);
        }
        printf("\n");
    }
}


int main() {
    int choice;
    while (1) {
        printf("\n--- Directed Graph Operations ---\n");
        printf("1. Create Graph\n");
        printf("2. Display Graph (Adjacency Matrix & List)\n");
        printf("3. Depth First Search (DFS)\n");
        printf("4. Breadth First Search (BFS)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                createGraph();
                break;
            case 2:
                display();
                break;
            case 3:
                DFS();
                break;
            case 4:
                BFS();
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

