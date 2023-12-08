#include <stdlib.h>
#include "queue.h"

#define _assert(expr) ((void)0)
//https://blog.csdn.net/qq_41028985/article/details/82859199---参考网址，涉及到单链表的头插法和尾插法！！


LinkQueue Qu;

char InitQueue(LinkQueue *Q)
{
    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if(Q->front == NULL)
        return(0);
    Q->front->next = NULL;
    return(1);
}

void DestroyQueue(LinkQueue *Q)
{
    _assert(Q != NULL);
    while(Q->front)
    {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
}

char QueueEmpty(LinkQueue Q)
{
	_assert(Q.front != NULL && Q.rear != NULL);
	
    if(Q.front == Q.rear)
        return(1);
    else
        return(0);
}

int QueueLength(LinkQueue Q)
{	
    QueuePtr p = Q.front;
    int Length = 0;
	
	_assert(Q.front != NULL);
    while(p != Q.rear)
    {
        Length++;
        p = p->next;
    }
return Length;
}

char GetHead(LinkQueue Q, ElemType *e)
{
	_assert(Q.front != NULL);
    if(QueueEmpty(Q))
        return(0);
    else
    {
        *e = Q.front->next->data;
        return(1);
    }
}

void QueueTraverse(LinkQueue Q, void (*fp)(ElemType))
{		
    QueuePtr p = Q.front->next;
	_assert(Q.front != NULL);
    while(p)
    {
        (*fp)(p->data);
        p = p->next;
    }
}

void ClearQueue(LinkQueue *Q)
{ 	
	QueuePtr p = Q->front;
	int Length = QueueLength(*Q);
    while(Length--)
    {
        p->next->data = 0;
        p = p->next;
    }
}


char EnQueue(LinkQueue *Q, ElemType e)
{
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if(p==NULL)
        return(0);
    p->data = e;
    p->next = NULL;
		
    Q->rear->next = p;
    Q->rear = p;
return(1);
}

char DeQueue(LinkQueue *Q, ElemType *e)
{
  QueuePtr p;

	  if(Q->front == Q->rear)
        return(0);

    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if(Q->rear == p)
        Q->rear = Q->front;

    free(p);
return(1);
}

char LineQueue(LinkQueue *Q, int len)
{
    int i;
    QueuePtr p = Q->front;

    for(i=1; i<len; i++)             
        if(p->next->data == p->next->next->data-1)
            p = p->next;
        else
            return(0);    

return(1);
} 
