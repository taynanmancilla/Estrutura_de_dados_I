#include<stdio.h>
#include<stdlib.h>
#include"ex014.h"

typedef struct _node{
    int val;
    struct _node *next;
} Node;

typedef struct _list{
    Node *begin;
    Node *end;
    int size;
} List;

typedef struct _queue{
    List *data;
} Queue;

//-----------------List-----------------

Node *Node_create(int val)
{
    Node *node = (Node*)calloc(1, sizeof(Node));
    node->next = NULL;
    node->val = val;

    return node;
}
List *List_create()
{
    List *L = (List*)calloc(1, sizeof(List));
    L->begin = NULL;
    L->end = NULL;
    L->size = 0;

    return L;
}
void Destroy_List(List **Ref_list)
{
    List *L = *Ref_list;
    Node *p = L->begin;

    while(p != NULL){
        Node *aux = p;
        p = p->next;
        free(aux);
    }
    free(L);
    *Ref_list = NULL;
}
bool is_Empty_List(const List *L)
{
    return L->size == 0;
}
int List_size(const List *L)
{
    return L->size;
}
void Add_Last_List(List *L, int val)
{
    Node *new = Node_create(val);
    if(is_Empty_List(L)){
        L->begin = L->end = new;
    }else{
        L->end->next = new;
        L->end = L->end->next;
    }
    L->size++;
}
void Remove_First_List(List *L)
{
    if(!is_Empty_List(L)){
        Node *p = L->begin;
        if(L->begin == L->end){ // Lista com apenas 1 elemento
            L->begin = NULL;
            L->end = NULL;
        }else{ // Lista com mais de 1 elemento
            L->begin = L->begin->next;
        }
        free(p); // Remove o primeiro elemento
        L->size--;
    }
}
void print_List(const List *L)
{
    Node *p = L->begin;
    printf("Fila = ");
    while(p != NULL){
        printf("|%d|->", p->val);
        p = p->next;
    }
    printf("NULL\n");
    printf("Size: %d\n", L->size);
    printf("Begin: %d\n", L->begin->val);
    printf("End: %d\n", L->end->val);
}

//-----------------Queue-----------------

Queue *create_Queue()
{
    Queue *Q = (Queue*)calloc(1, sizeof(Queue));
    Q->data = List_create();
    return Q;
}
void destroy_Queue(Queue **Q_Ref)
{
    Queue *Q = *Q_Ref;
    Destroy_List(&Q->data);
    free(Q);
    *Q_Ref = NULL;
}

bool is_empty_Queue(const Queue *Q)
{
    return is_Empty_List(Q->data);
}
int size_Queue(const Queue *Q)
{
    return List_size(Q->data);
}

void enqueue_Queue(Queue *Q, int info)
{
    Add_Last_List(Q->data, info);
}

int dequeue_Queue(Queue *Q)
{
    if(is_empty_Queue(Q)){
        fprintf(stderr, "Erro em Dequeue()\n");
        fprintf(stderr, "Fila Vazia!\n");
        exit(EXIT_FAILURE);
    }
    int val = Q->data->begin->val;
    Remove_First_List(Q->data);
    return val;
}

int peek_Queue(const Queue *Q)
{
    if(is_Empty_List(Q->data) || is_empty_Queue(Q)){
        fprintf(stderr, "Erro em Peek()\n");
        fprintf(stderr, "Fila Vazia!\n");
        exit(EXIT_FAILURE);
    }
    return Q->data->begin->val;
}

void print_Queue(const Queue *Q)
{
    print_List(Q->data);
}
