/*
 *DynaLnkQueue.h
 */

#ifndef _DYNALNKQUEUE_H
#define _DYNALNKQUEUE_H

#define ElemType   int

typedef struct Node
{
    int data;
    struct Node *next;
}QNode, *QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

char InitQueue(LinkQueue*);
void DestroyQueue(LinkQueue*);
char QueueEmpty(LinkQueue);
int  QueueLength(LinkQueue);
char GetHead(LinkQueue, ElemType*);
void QueueTraverse(LinkQueue, void(*)(ElemType));
void ClearQueue(LinkQueue*);
char EnQueue(LinkQueue*, ElemType);
char DeQueue(LinkQueue*, ElemType*);
char LineQueue(LinkQueue*, int);

#endif /* _DYNALNKQUEUE_H */
