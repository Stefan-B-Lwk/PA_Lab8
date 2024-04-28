/*parcurgerge  graf cu DFS/BFS*/

#include <stdlib.h>
#include <stdio.h>

typedef struct NODE
{
    int data;
    struct NODE *next;
} NODE;

typedef struct GPH
{
    int vertices;
    int *visited;
    struct NODE **adjacency_lists;
} GPH;


/// utils
NODE *createNode(int v)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GPH *createGraph(int vertices)
{
    int i;
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE));

    graph->visited = malloc(sizeof(int) * vertices);
    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}
void addEdge(GPH *graph, int src, int dest)
{
    NODE *new_node = createNode(dest);

    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = createNode(src);

    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}
int *insertEdges(int nr_vertices, int nr_edges, GPH *graph)
{
    int src, dest, i;
    printf("adauga %d muchii (de la 0 la %d)\n", nr_edges, nr_vertices - 1);

    for (i = 0; i < nr_edges; i++)
    {
        scanf("%d%d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

/// bfs utils
int isEmpty(NODE *queue)
{
    return queue == NULL;
}

void enqueue(NODE **queue, int data)
{
    NODE *new_node = createNode(data);

    if (*queue == NULL)
    {
        *queue = new_node;
        return;
    }
    else
    {
        NODE *temp = *queue;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE **queue)
{

    if (*queue == NULL)
    {
        printf("e gol q");
        return -1;
    }

    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void printGraph(GPH *graph)
{
    int i;
    for (i = 0; i < graph->vertices; i += 1)
    {
        NODE *temp = graph->adjacency_lists[i];

        while (temp)
        {
            printf("%d ", temp->data);
            temp = (temp->next);
        }
        printf("\n");
    }
}

void printQueue(NODE *queue)
{
    while (queue != NULL)
    {
        printf("%d ", queue->data);
        queue = (queue->next)->next;
    }
}

void wipeVisitedList(GPH *graph, int nr_vertices)
{
    for (int i = 0; i < nr_vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

// parcurgeri
void DFS(GPH *graph, int vertex_nr)
{
    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    printf("%d->", vertex_nr);

    while (temp != NULL)
    {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(GPH *graph, int start)
{
    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!(isEmpty(queue)))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->adjacency_lists[current];

        while (temp)
        {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }

            temp = temp->next;
        }
    }
}

int main()
{

    int nr_vertices, nr_edges;
    int src, dest;
    int starting_vertex;

    printf("cate noduri are graful?");
    scanf("%d", &nr_vertices);
    printf("cate muchii are graful?");
    scanf("%d", &nr_edges);

    GPH *graph = createGraph(nr_vertices);

    insertEdges(nr_vertices, nr_edges, graph);


    printf("de unde plecam in DFS?");
    scanf("%d", &starting_vertex); // =))) misto comentarii

    printf("parcurgere cu DFS:");
    DFS(graph, starting_vertex);
    
    wipeVisitedList(graph, nr_vertices);
    printf("\n");

    printf("de unde plecam in BFS?");
    scanf("%d", &starting_vertex);

    printf("parcurgere cu BFS:");
    BFS(graph, starting_vertex);


    return 0;
}
