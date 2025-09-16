/**
 * @file LinkedListStack.c
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2025-09-04
 *
 * @copyright Copyright (c) 2025
 *
 */
/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include "LinkedListStack.h"
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
void  LLS_CreateStack( LinkedListStack** Stack )
{
    *Stack = (LinkedListStack*)malloc( sizeof(LinkedListStack) );

    if ( *Stack == NULL )
    {
        fprintf( stderr, "Error: Memory allocation failed in %s()\n", __func__ );
        exit(EXIT_FAILURE);
    }

    (*Stack)->List = NULL;
    (*Stack)->Top  = NULL;
}
void  LLS_DestroyStack( LinkedListStack* Stack )
{
    Node* Current;
    Node* Next;

    if ( Stack == NULL )
        return;

    Current = Stack->List;

    while ( Current != NULL )
    {
        Next = Current->NextNode;

        LLS_DestroyNode(Current);

        Current = Next;
    }

    free(Stack);
}

Node* LLS_CreateNode( char* Data )
{
    Node* NewNode = (Node*)malloc( sizeof(Node) );

    if ( NewNode == NULL )
    {
        fprintf( stderr, "Error: Memory allocation failed in %s()\n", __func__ );
        exit(EXIT_FAILURE);
    }

    NewNode->Data = (char*)malloc( strlen(Data) + 1 );

    if ( NewNode->Data == NULL )
    {
        fprintf( stderr, "Error: Memory allocation failed in %s()\n", __func__ );
        free(NewNode);
        exit(EXIT_FAILURE);
    }

    strcpy( NewNode->Data, Data );
    NewNode->NextNode = NULL;

    return NewNode;
}
void  LLS_DestroyNode( Node* _Node )
{
    if ( _Node == NULL )
        return;

    if ( _Node->Data != NULL )
        free( _Node->Data );

    free(_Node);
}

void  LLS_Push( LinkedListStack* Stack, Node* NewNode )
{
    if ( Stack == NULL || NewNode == NULL )
        return;

    if ( Stack->List == NULL )
    {
        Stack->List = NewNode;
        Stack->Top  = NewNode;
    }
    else
    {
        NewNode->NextNode = Stack->Top;
        Stack->Top = NewNode;
    }
}
Node* LLS_Pop( LinkedListStack* Stack )
{
    Node* Popped;

    if ( Stack == NULL || Stack->Top == NULL )
        return NULL;

    Popped = Stack->Top;
    Stack->Top = Stack->Top->NextNode;

    if ( Stack->Top == NULL )
        Stack->List = NULL;

    Popped->NextNode = NULL;

    return Popped;
}

Node* LLS_Top( LinkedListStack* Stack )
{
    if ( Stack == NULL )
        return NULL;

    return Stack->Top;
}
int   LLS_GetSize( LinkedListStack* Stack )
{
    int Count = 0;
    Node* Current;

    if ( Stack == NULL )
        return 0;

    Current = Stack->Top;

    while ( Current != NULL )
    {
        Count++;
        Current = Current->NextNode;
    }

    return Count;
}
int   LLS_IsEmpty( LinkedListStack* Stack )
{
    if ( Stack == NULL )
        return 1;

    return ( Stack->Top == NULL );
}