/**
 * @file CircularQueue.c
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2025-09-16
 *
 * @copyright Copyright (c) 2025
 *
 */
/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include "CircularQueue.h"
/*------------------------------------------------------------------------------
------
------    Defines and Types
------
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
------
------    Macro
------
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
------
------    variables(external)
------
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
------
------    Functions
------
------------------------------------------------------------------------------*/
void        CQ_CreateQueue( CircularQueue** Queue, int Capacity)
{
    *Queue = (CircularQueue*)malloc( sizeof(CircularQueue) );
    if ( *Queue == NULL )
    {
        fprintf( stderr, "Error: Not enough memory!\n" );
        exit( EXIT_FAILURE );
    }

    (*Queue)->Capacity = Capacity;
    (*Queue)->Front    = 0;
    (*Queue)->Rear     = 0;

    (*Queue)->Nodes = (Node*)malloc( sizeof(Node) * (*Queue)->Capacity + 1 );
    if ( (*Queue)->Nodes == NULL )
    {
        fprintf( stderr, "Error: Not enough memory!\n" );
        free( *Queue );
        exit( EXIT_FAILURE );
    }
}
void        CQ_DestroyQueue( CircularQueue* Queue )
{
    if ( Queue != NULL )
    {
        if ( Queue->Nodes != NULL )
        {
            free( Queue->Nodes );
        }
        free( Queue );
    }
}
void        CQ_Enqueue( CircularQueue* Queue, ElementType Data)
{
    if ( CQ_IsFull( Queue ) )
    {
        fprintf( stderr, "Error: Circular Queue is full!\n" );
        exit( EXIT_FAILURE );
    }
    Queue->Nodes[ Queue->Rear ].Data = Data;
    Queue->Rear = ( Queue->Rear + 1 ) % (Queue->Capacity + 1);
}
ElementType CQ_Dequeue( CircularQueue* Queue )
{
    ElementType data;

    if (CQ_IsEmpty(Queue))
    {
        fprintf( stderr, "Error: Circular Queue is empty!\n" );
        exit( EXIT_FAILURE );
    }

    data = Queue->Nodes[ Queue->Front ].Data;
    Queue->Front = ( Queue->Front + 1 ) % (Queue->Capacity + 1);
    return data;
}
int         CQ_GetSize( CircularQueue* Queue )
{
    return ( Queue->Rear - Queue->Front + (Queue->Capacity + 1) ) % (Queue->Capacity + 1);
}
int         CQ_IsEmpty( CircularQueue* Queue )
{
    return Queue->Front == Queue->Rear;
}
int         CQ_IsFull( CircularQueue* Queue )
{
    return ( ( Queue->Rear + 1 ) % (Queue->Capacity + 1) ) == Queue->Front;
}