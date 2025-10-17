#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int adj[MAX][MAX];
int n;
int visited[MAX];

// --- Create Adjacency Matrix ---
void createGraph() {
    int i, j, edges, src, dest;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (src dest):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d%d", &src, &dest);
        adj[src][dest] = 1; // Directed graph
    }
}

// --- Display Adjacency Matrix ---
void displayMatrix() {
    int i, j;
    printf("\nAdjacency Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%d ", adj[i][j]);
        printf("\n");
    }
}

// --- Display Adjacency List ---
void displayList() {
    int i, j;
    printf("\nAdjacency List:\n");
    for (i = 0; i < n; i++) {
        printf("%d -> ", i);
        for (j = 0; j < n; j++) {
            if (adj[i][j] == 1)
                printf("%d ", j);
        }
        printf("\n");
    }
}

// --- DFS using Recursion ---
void DFS(int v) {
    int i;
    visited[v] = 1;
    printf("%d ", v);
    for (i = 0; i < n; i++) {
        if (adj[v][i] == 1 && !visited[i])
            DFS(i);
    }
}

// --- BFS using Queue ---
void BFS(int start) {
    int queue[MAX], front = 0, rear = 0, i;
    for (i = 0; i < n; i++)
        visited[i] = 0;

    printf("%d ", start);
    visited[start] = 1;
    queue[rear++] = start;

    while (front != rear) {
        int v = queue[front++];
        for (i = 0; i < n; i++) {
            if (adj[v][i] == 1 && !visited[i]) {
                printf("%d ", i);
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

int main() {
    int choice, start;

    while (1) {
        printf("\n\n--- Directed Graph Operations ---\n");
        printf("1. Create Graph\n2. Display Adjacency Matrix\n3. Display Adjacency List\n4. DFS\n5. BFS\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createGraph(); break;
            case 2: displayMatrix(); break;
            case 3: displayList(); break;
            case 4:
                for (int i = 0; i < n; i++) visited[i] = 0;
                printf("Enter starting vertex: ");
                scanf("%d", &start);
                printf("DFS Traversal: ");
                DFS(start);
                printf("\n");
                break;
            case 5:
                printf("Enter starting vertex: ");
                scanf("%d", &start);
                printf("BFS Traversal: ");
                BFS(start);
                printf("\n");
                break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}
