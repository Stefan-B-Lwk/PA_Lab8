/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;
/// pentru simplitate, folosim int uri pt a numi restaurantele/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct GPH
{
    int nr_nodes;
    int *vis; //vis de la visited
    struct Node **adj_list;
} GPH;

typedef struct STK
{
    int t;
    int stack_limit;
    int *arr;
} STK;

Node *createNode(int v)
{
    Node *nn = malloc(sizeof(Node));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void addEdge(GPH *graph, int src, int dest)
{
    Node *nn = createNode(dest);
    nn->next = graph->adj_list[src];
    graph->adj_list[src] = nn;

    nn = createNode(src);
    nn->next = graph->adj_list[dest];
    graph->adj_list[dest] = nn;
}

GPH *createGraph(int nr_nodes)
{
    int i;

    GPH *graph = malloc(sizeof(GPH));
    graph->nr_nodes = nr_nodes;
    graph->adj_list = malloc(sizeof(Node) * nr_nodes);
    graph->vis = malloc(sizeof(int) * nr_nodes);

    for (int i = 0; i < nr_nodes; i++)
    {
        graph->adj_list[i] = NULL;
        graph->vis[i] = 0;
    }
    return graph;
}

STK *createStack(int stack_limit)
{
    STK *stack = malloc(sizeof(STK));
    stack->arr = malloc(stack_limit * sizeof(int));
    stack->t = -1;
    stack->stack_limit = stack_limit;

    return stack;
}

void push(int pushed_value, STK *stack)
{
    stack->t = stack->t + 1;
    stack->arr[stack->t] = pushed_value;
}

void DFS(GPH *graph, STK *stack, int vertex)
{
    Node *adj_list = graph->adj_list[vertex];
    Node *aux = adj_list;

    graph->vis[vertex] = 1;
    printf("%d ", vertex);
    
    push(vertex, stack);
    while (aux != NULL)
    {
        int con_vertex = aux->data;
        if (graph->vis[con_vertex] == 0)
            DFS(graph, stack, con_vertex);
        aux = aux->next;
    }
}

void insertEdges(GPH *graph, int nr_edges, int nr_nodes)
{
    int src, dest, i;
    printf("adauga %d munchii (de la 1 la %d)\n", nr_edges, nr_nodes);

    for (i = 0; i < nr_edges; i++)
    {
        scanf("%d%d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

void wipe(GPH *graph, int nr_nodes)
{
    for (int i = 0; i < nr_nodes; i++)
    {
        graph->vis[i] = 0;
    }
}

int findRoad(GPH *graph, int nr_nodes, STK *stack_1, STK *stack_2, int vertex_1, int vertex_2) // 0 sau 1 daca poate fi sau nu ajuns
{

    DFS(graph, stack_1, vertex_1);
    wipe(graph, nr_nodes);
    DFS(graph, stack_2, vertex_2);

    for (int i = 0; i <= (stack_1->t); i++) // aici i tine loc de numar adica de restaurant{for (int j = 0; j < 5; j++)
    {

        for (int j = 0; j <= (stack_2->t); j++)
        {
            if (stack_1->arr[i] == stack_2->arr[j])
            {
                return 1;
            }
        }
    }

    return 0;
}

int main()
{

    int nr_nodes, nr_edges, src, dest, i, vertex_1, vertex_2, answer;

    printf("cate noduri are girafa/graful?");
    scanf("%d", &nr_nodes);

    printf("cate muchii are graful/girafa?");
    scanf("%d", &nr_edges);

    GPH *graph = createGraph(nr_nodes);

    STK *stack_1 = createStack(2 * nr_nodes);
    STK *stack_2 = createStack(2 * nr_nodes);

    insertEdges(graph, nr_edges, nr_nodes);

    vertex_1 = 5;
    vertex_2 = 3;

    printf("\n%d", findRoad(graph, nr_nodes, stack_1, stack_2, vertex_1, vertex_2));

    return 0;
}
