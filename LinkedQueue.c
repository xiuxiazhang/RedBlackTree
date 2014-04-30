#include <stdio.h>
#include <stdlib.h>
#include "redblack.h"
#define IN
#define OUT
#define NodeType RbTreePtr 
#define NodeType void *
extern struct RedBlackNode nilNode;
typedef struct link
{
    NodeType data;
    struct link *next;
}LinkedList;

typedef struct
{
    LinkedList *front;
    LinkedList *rear;
}LinkedQueue;

void InitQueue(LinkedQueue **lq)
{
    *lq=(LinkedQueue *)malloc(sizeof(LinkedQueue));
    (*lq)->front=NULL;
    (*lq)->rear=NULL;
}

void EnQueue(LinkedQueue **lq,NodeType x)
{
    LinkedList *node=(LinkedList*)malloc(sizeof(LinkedList));
    node->data=x;
    node->next=NULL;
    LinkedQueue *list=*lq;
    if(list->front==NULL&&list->rear==NULL) //the queue is empty
    {
        list->front=node;
        list->rear=node;
    }
    else
    {
    list->rear->next=node;
    list->rear=node;
    }
    *lq=list;

}

int DeQueue(LinkedQueue **lq,OUT NodeType *x)
{
    if((*lq)->front==NULL&&(*lq)->rear==NULL)
    {
        printf("the queue is empty, can not dequeue!\n");
        return 0;
    }
    else
    {
        LinkedList *q =(*lq)->front;
        *x=q->data;
        if((*lq)->front==(*lq)->rear) // the queue has only one node ,when delete a node ,it becomes empty
        {
            (*lq)->front=(*lq)->rear=NULL;
        }
        else
        {
        (*lq)->front=q->next;
        }
        free(q);
    }
}

int GetHead(LinkedQueue *lq,NodeType *x)
{
    if(lq->front==lq->rear&&lq->front==NULL)
    {
        printf("the queue is empty,we can not get its head node!\n");
        return 0;
    }
    else
    {
        *x=lq->front->data;
        return 1;
    }
}

int QueueEmpty(LinkedQueue *lq)
{
    if(lq->front==NULL&&lq->rear==NULL)
        return 1;
    else
        return 0;
}
void DispNode(NodeType x)
{
    printf("%d  %d\t",x->key,x->value);
}
void DispQueue(LinkedQueue *lq)
{
    LinkedList *ll=lq->front;
    while(ll!=NULL)
    {
       // printf("%d\t",ll->data);
        DispNode(ll->data);
        ll=ll->next;
    }
    printf("\n");
}


int TreeBFS(RbTreePtr T)
{
    LinkedQueue *lq;
    RbTreePtr x;
    int up,down;
    InitQueue(&lq);
    EnQueue(&lq,T);
    if (T== &nilNode)
        return 0; // Null tree
    up=1;
    down=0;
    while(!QueueEmpty(lq))
    {
        DeQueue(&lq,&x);
        if(up==0)
        {
        printf("\n");
        up=down;
        down=0;
        }
        //else
        DispNode(x);

        if(x->left !=  &nilNode)
        {
            EnQueue(&lq,x->left);
            down ++;
        }
        if(x->right !=  &nilNode)
        {
            EnQueue(&lq,x->right);
            down ++;
        }
        up--;
    }
    return 1;
}
#if 0
int main()
{
    LinkedQueue *lq;
    InitQueue(&lq);
    EnQueue(&lq,1);
    EnQueue(&lq,2);
    EnQueue(&lq,3);
    EnQueue(&lq,4);
    DispQueue(lq);
    NodeType x;
    DeQueue(&lq,&x);
    DispQueue(lq);
    GetHead(lq,&x);
    printf("gettop=%d\n",x);
    return 0;
}
#endif
