#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES]; // �θ� ���

// ���� ����ü
struct Edge {
    int start, end, weight;
};

// �׷����� ���� ����ü ����
typedef struct GraphType {
    int n; // ������ ����
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

// �ʱ�ȭ
void set_init(int n) {
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

// curr�� ���ϴ� ������ ��ȯ�Ѵ�.
int set_find(int curr) {
    if (parent[curr] == -1)
        return curr; // ��Ʈ
    while (parent[curr] != -1)
        curr = parent[curr];
    return curr;
}

// �ΰ��� ���Ұ� ���� ������ ��ģ��.
void set_union(int a, int b) {
    int root1 = set_find(a); // ��� a�� ��Ʈ�� ã�´�.
    int root2 = set_find(b); // ��� b�� ��Ʈ�� ã�´�.
    if (root1 != root2) // ���Ѵ�.
        parent[root1] = root2;
}

// �׷��� �ʱ�ȭ
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}

// Min-Heapify �Լ�
void min_heapify(struct Edge arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].weight < arr[smallest].weight)
        smallest = left;

    if (right < n && arr[right].weight < arr[smallest].weight)
        smallest = right;

    if (smallest != i) {
        struct Edge temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        min_heapify(arr, n, smallest);
    }
}

// Min-Heap ����
void min_heap_sort(struct Edge arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        min_heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        struct Edge temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        min_heapify(arr, i, 0);
    }
}

// Kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
void kruskal(GraphType* g) {
    int edge_accepted = 0; // ������� ���õ� ������ ��
    int uset, vset; // ���� u�� ���� v�� ���� ��ȣ
    struct Edge e;

    set_init(g->n); // ���� �ʱ�ȭ
    min_heap_sort(g->edges, g->n); // Min-Heap ������ ����Ͽ� ������ ����

    printf("Kruskal MST Algorithm(minheap)\n");
    int i = g->n - 1;
    while (edge_accepted < (g->n - 1)) // ������ �� < (n-1)
    {
        e = g->edges[i];
        uset = set_find(e.start); // ���� u�� ���� ��ȣ
        vset = set_find(e.end); // ���� v�� ���� ��ȣ
        if (uset != vset) { // ���� ���� ������ �ٸ���
            printf("Edge (%d,%d) Select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset); // �� ���� ������ ��ģ��.
        }
        i--;
    }
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    insert_edge(g, 1, 6, 11);
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 6, 5, 9);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 9, 10, 10);

    kruskal(g);
    free(g);
    return 0;
}