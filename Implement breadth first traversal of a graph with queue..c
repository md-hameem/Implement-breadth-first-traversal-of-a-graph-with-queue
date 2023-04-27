#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAX_VERTICES 100

typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

typedef struct {
    int vertices;
    int **adj_matrix;
} Graph;

Graph *create_graph(int vertices);

Queue *create_queue();
int is_empty(Queue *q);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);
void add_edge(Graph *graph, int src, int dest);
void print_graph(Graph *graph);
void bfs(Graph *graph, int start_vertex);

int main() {
    int num_vertices = 6;
    Graph *graph = create_graph(num_vertices);

    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 4);
    add_edge(graph, 2, 3);
    add_edge(graph, 3, 4);
    add_edge(graph, 4, 5);

    print_graph(graph);

    printf("BFS Traversal: ");
    bfs(graph, 0);

    free(graph->adj_matrix);
    free(graph);

    return 0;
}

Queue *create_queue() {
    Queue *q = malloc(sizeof(Queue));
    if (q == NULL) {
        perror("Error: memory allocation failed");
        exit(EXIT_FAILURE);
    }
    q->front = -1;
    q->rear = -1;
    return q;
}

int is_empty(Queue *q) {
    return q->rear == -1;
}

void enqueue(Queue *q, int value) {
    if (q->rear == MAX_VERTICES - 1) {
        printf("Queue is full\n");
        exit(EXIT_FAILURE);
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue *q) {
    if (is_empty(q)) {
        printf("Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

Graph *create_graph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    if (graph == NULL) {
        perror("Error: memory allocation failed");
        exit(EXIT_FAILURE);
    }
    graph->vertices = vertices;

    graph->adj_matrix = malloc(vertices * sizeof(int *));
    if (graph->adj_matrix == NULL) {
        perror("Error: memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < vertices; i++) {
        graph->adj_matrix[i] = calloc(vertices, sizeof(int));
        if (graph->adj_matrix[i] == NULL) {
            perror("Error: memory allocation failed");
            exit(EXIT_FAILURE);
        }
    }
    return graph;
}

void add_edge(Graph *graph, int src, int dest) {
    graph->adj_matrix[src][dest] = 1;
    graph->adj_matrix[dest][src] = 1;
}

void print_graph(Graph *graph) {
    printf("Adjacency matrix:\n");
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->adj_matrix[i][j]);
        }
        printf("\n");
    }
}

void bfs(Graph *graph, int start_vertex) {
    int visited[MAX_VERTICES] = {0};
    Queue *q = create_queue();

    visited[start_vertex] = 1;
    enqueue(q, start_vertex);

    while (!is_empty(q)) {
        int current_vertex = dequeue(q);
        printf("%d ", current_vertex);

        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adj_matrix[current_vertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(q, i);
            }
        }
    }
}

