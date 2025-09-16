/**
 * @file LinkedQueue.c
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
#include "LinkedQueue.h"
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
void  LQ_CreateQueue( LinkedQueue** Queue )
{
    *Queue = (LinkedQueue*)malloc( sizeof( LinkedQueue ) );

    if ( *Queue == NULL )
    {
        printf( "Error, Memory Allocate Fail\n" );
        return;
    }

    ( *Queue )->Front = NULL;
    ( *Queue )->Rear  = NULL;
    ( *Queue )->Count = 0;
}
void  LQ_DestroyQueue( LinkedQueue* Queue )
{
    if ( Queue != NULL )
    {
        while ( !LQ_IsEmpty( Queue ) )
        {
            Node* node = LQ_Dequeue( Queue );
            LQ_DestroyNode( node );
        }
        free( Queue );
    }
}

Node* LQ_CreateNode(char* Data)
{
    Node* newNode = (Node*)malloc( sizeof( Node ) );

    if ( newNode == NULL )
    {
        printf( "Error, Memory Allocate Fail\n" );
        return NULL;
    }

    newNode->Data     = (char*)malloc( strlen( Data ) + 1 );
    newNode->NextNode = NULL;

    if ( newNode->Data == NULL )
    {
        printf( "Error, Memory Allocate Fail\n" );
        free( newNode );
        return NULL;
    }

    strcpy( newNode->Data, Data );

    return newNode;
}
void  LQ_DestroyNode(Node* _Node )
{
    if ( _Node != NULL )
    {
        if ( _Node->Data != NULL )
        {
            free( _Node->Data );
        }
        free( _Node );
    }
}

void  LQ_Enqueue( LinkedQueue* Queue, Node* NewNode )
{
    if ( Queue == NULL || NewNode == NULL )
    {
        return;
    }

    if ( LQ_IsEmpty( Queue ) )
    {
        Queue->Front = NewNode;
        Queue->Rear  = NewNode;
    }
    else
    {
        Queue->Rear->NextNode = NewNode;
        Queue->Rear           = NewNode;
    }

    Queue->Count++;
}
Node* LQ_Dequeue( LinkedQueue* Queue )
{
    if ( Queue == NULL || LQ_IsEmpty( Queue ) )
    {
        return NULL;
    }

    Node* Dequeued = Queue->Front;

    Queue->Front = Queue->Front->NextNode;
    Dequeued->NextNode = NULL;

    Queue->Count--;

    if ( LQ_IsEmpty( Queue ) )
    {
        Queue->Rear = NULL;
    }

    return Dequeued;
}

int   LQ_IsEmpty( LinkedQueue* Queue )
{
    if ( Queue == NULL || Queue->Count == 0 )
    {
        return 1;
    }
    return 0;
}