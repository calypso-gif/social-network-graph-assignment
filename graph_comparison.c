#include <stdio.h>
#include <stdlib.h>

#define V 6

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

char vertices[V] = {'A', 'B', 'C', 'D', 'E', 'F'};

int indexOfVertex(char ch)
{
    for (int i = 0; i < V; i++) {
        if (vertices[i] == ch)
            return i;
    }
    return -1;
}

void addEdgeMatrix(int matrix[V][V], char u, char v)
{
    int i = indexOfVertex(u);
    int j = indexOfVertex(v);

    matrix[i][j] = 1;
    matrix[j][i] = 1;
}

void addEdgeListOneWay(Node *adj[V], int from, int to)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->vertex = to;
    newNode->next = NULL;

    if (adj[from] == NULL) {
        adj[from] = newNode;
    } else {
        Node *ptr = adj[from];

        while (ptr->next != NULL)
            ptr = ptr->next;

        ptr->next = newNode;
    }
}

void addEdgeList(Node *adj[V], char u, char v)
{
    int i = indexOfVertex(u);
    int j = indexOfVertex(v);

    /* The graph is undirected, so store both directions. */
    addEdgeListOneWay(adj, i, j);
    addEdgeListOneWay(adj, j, i);
}

void displayMatrix(int matrix[V][V])
{
    printf("\nADJACENCY MATRIX\n\n");

    printf("  ");
    for (int i = 0; i < V; i++)
        printf("%c ", vertices[i]);
    printf("\n");

    for (int i = 0; i < V; i++) {
        printf("%c ", vertices[i]);
        for (int j = 0; j < V; j++)
            printf(" %d", matrix[i][j]);
        printf("\n");
    }
}

void displayList(Node *adj[V])
{
    printf("\nADJACENCY LIST\n\n");

    for (int i = 0; i < V; i++) {
        printf("%c -> ", vertices[i]);

        Node *ptr = adj[i];
        while (ptr != NULL) {
            printf("%c", vertices[ptr->vertex]);
            if (ptr->next != NULL)
                printf(" -> ");
            ptr = ptr->next;
        }

        printf(" -> NULL\n");
    }
}

void bfsMatrix(int matrix[V][V], char start)
{
    int visited[V] = {0};
    int queue[V];
    int front = 0, rear = 0;
    int checks = 0;
    int startIndex = indexOfVertex(start);

    visited[startIndex] = 1;
    queue[rear++] = startIndex;

    printf("\nBFS (Adjacency Matrix): ");

    while (front < rear) {
        int u = queue[front++];
        printf("%c ", vertices[u]);

        /* Matrix must check all V columns for each visited vertex. */
        for (int v = 0; v < V; v++) {
            checks++;

            if (matrix[u][v] == 1 && !visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
            }
        }
    }

    printf("\nNeighbor checks = %d\n", checks);
}

void dfsMatrixUtil(int matrix[V][V], int u, int visited[V], int *checks)
{
    visited[u] = 1;
    printf("%c ", vertices[u]);

    for (int v = 0; v < V; v++) {
        (*checks)++;

        if (matrix[u][v] == 1 && !visited[v])
            dfsMatrixUtil(matrix, v, visited, checks);
    }
}

void dfsMatrix(int matrix[V][V], char start)
{
    int visited[V] = {0};
    int checks = 0;
    int startIndex = indexOfVertex(start);

    printf("\nDFS (Adjacency Matrix): ");
    dfsMatrixUtil(matrix, startIndex, visited, &checks);
    printf("\nNeighbor checks = %d\n", checks);
}

void bfsList(Node *adj[V], char start)
{
    int visited[V] = {0};
    int queue[V];
    int front = 0, rear = 0;
    int checks = 0;
    int startIndex = indexOfVertex(start);

    visited[startIndex] = 1;
    queue[rear++] = startIndex;

    printf("\nBFS (Adjacency List): ");

    while (front < rear) {
        int u = queue[front++];
        printf("%c ", vertices[u]);

        /* List checks only the neighbours that actually exist. */
        Node *ptr = adj[u];
        while (ptr != NULL) {
            checks++;

            int v = ptr->vertex;
            if (!visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
            }

            ptr = ptr->next;
        }
    }

    printf("\nNeighbor checks = %d\n", checks);
}

void dfsListUtil(Node *adj[V], int u, int visited[V], int *checks)
{
    visited[u] = 1;
    printf("%c ", vertices[u]);

    Node *ptr = adj[u];
    while (ptr != NULL) {
        (*checks)++;

        int v = ptr->vertex;
        if (!visited[v])
            dfsListUtil(adj, v, visited, checks);

        ptr = ptr->next;
    }
}

void dfsList(Node *adj[V], char start)
{
    int visited[V] = {0};
    int checks = 0;
    int startIndex = indexOfVertex(start);

    printf("\nDFS (Adjacency List): ");
    dfsListUtil(adj, startIndex, visited, &checks);
    printf("\nNeighbor checks = %d\n", checks);
}

/* Search for a target vertex from A using BFS and count neighbour checks. */
int searchVertexMatrix(int matrix[V][V], char start, char target, int *checks)
{
    int visited[V] = {0};
    int queue[V];
    int front = 0, rear = 0;
    int startIndex = indexOfVertex(start);
    int targetIndex = indexOfVertex(target);

    *checks = 0;
    visited[startIndex] = 1;
    queue[rear++] = startIndex;

    while (front < rear) {
        int u = queue[front++];

        for (int v = 0; v < V; v++) {
            (*checks)++;

            if (matrix[u][v] == 1 && !visited[v]) {
                if (v == targetIndex)
                    return v;

                visited[v] = 1;
                queue[rear++] = v;
            }
        }
    }

    return -1;
}

int searchVertexList(Node *adj[V], char start, char target, int *checks)
{
    int visited[V] = {0};
    int queue[V];
    int front = 0, rear = 0;
    int startIndex = indexOfVertex(start);
    int targetIndex = indexOfVertex(target);

    *checks = 0;
    visited[startIndex] = 1;
    queue[rear++] = startIndex;

    while (front < rear) {
        int u = queue[front++];
        Node *ptr = adj[u];

        while (ptr != NULL) {
            (*checks)++;

            int v = ptr->vertex;
            if (!visited[v]) {
                if (v == targetIndex)
                    return v;

                visited[v] = 1;
                queue[rear++] = v;
            }

            ptr = ptr->next;
        }
    }

    return -1;
}

int edgeExistsMatrix(int matrix[V][V], char u, char v, int *checks)
{
    int i = indexOfVertex(u);
    int j = indexOfVertex(v);

    *checks = 1;
    return matrix[i][j];
}

int edgeExistsList(Node *adj[V], char u, char v, int *checks)
{
    int i = indexOfVertex(u);
    int j = indexOfVertex(v);
    Node *ptr = adj[i];

    *checks = 0;

    while (ptr != NULL) {
        (*checks)++;

        if (ptr->vertex == j)
            return 1;

        ptr = ptr->next;
    }

    return 0;
}

void freeList(Node *adj[V])
{
    for (int i = 0; i < V; i++) {
        Node *ptr = adj[i];

        while (ptr != NULL) {
            Node *temp = ptr;
            ptr = ptr->next;
            free(temp);
        }

        adj[i] = NULL;
    }
}

int main(void)
{
    int matrix[V][V] = {0};
    Node *adj[V] = {NULL};

    /* Given connections: A-B, A-C, B-D, B-E, C-F, E-F */
    addEdgeMatrix(matrix, 'A', 'B');
    addEdgeMatrix(matrix, 'A', 'C');
    addEdgeMatrix(matrix, 'B', 'D');
    addEdgeMatrix(matrix, 'B', 'E');
    addEdgeMatrix(matrix, 'C', 'F');
    addEdgeMatrix(matrix, 'E', 'F');

    addEdgeList(adj, 'A', 'B');
    addEdgeList(adj, 'A', 'C');
    addEdgeList(adj, 'B', 'D');
    addEdgeList(adj, 'B', 'E');
    addEdgeList(adj, 'C', 'F');
    addEdgeList(adj, 'E', 'F');

    displayMatrix(matrix);
    displayList(adj);

    bfsMatrix(matrix, 'A');
    dfsMatrix(matrix, 'A');
    bfsList(adj, 'A');
    dfsList(adj, 'A');

    char target = 'E';
    int searchChecksMatrix, searchChecksList;
    int foundMatrix = searchVertexMatrix(matrix, 'A', target, &searchChecksMatrix);
    int foundList = searchVertexList(adj, 'A', target, &searchChecksList);

    printf("\nSEARCH FOR VERTEX %c FROM A (BFS-BASED SEARCH)\n", target);
    if (foundMatrix != -1)
        printf("Matrix: %c found after %d neighbor checks\n",
               vertices[foundMatrix], searchChecksMatrix);
    else
        printf("Matrix: vertex not found\n");

    if (foundList != -1)
        printf("List:   %c found after %d neighbor checks\n",
               vertices[foundList], searchChecksList);
    else
        printf("List:   vertex not found\n");

    int edgeChecksMatrix, edgeChecksList;
    int edgeMatrix = edgeExistsMatrix(matrix, 'E', 'F', &edgeChecksMatrix);
    int edgeList = edgeExistsList(adj, 'E', 'F', &edgeChecksList);

    printf("\nEDGE CHECK: E-F\n");
    printf("Matrix: %s (%d check)\n",
           edgeMatrix ? "Edge exists" : "No edge", edgeChecksMatrix);
    printf("List:   %s (%d checks)\n",
           edgeList ? "Edge exists" : "No edge", edgeChecksList);

    freeList(adj);
    return 0;
}
