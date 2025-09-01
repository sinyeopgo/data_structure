/**
 * @file DoublyLinkedList.c
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief Doubly Linked List implementation
 * @version 0.1
 * @date 2025-09-01
 *
 * @copyright Copyright (c) 2025
 *
 */
/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include "DoublyLinkedList.h"
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
/**
 * @brief Create a new node.
 *
 * @param NewData
 * @return Node*
 */
Node* DLL_CreateNode( ElementType NewData )
{
    Node* NewNode = (Node*)malloc(sizeof(Node));
    if (NewNode == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    NewNode->Data = NewData;
    NewNode->PrevNode = NULL;
    NewNode->NextNode = NULL;
    return NewNode;
}
/**
 * @brief Destroy a node.
 *
 * @param Node
 */
void  DLL_DestroyNode( Node* Node)
{
    if (Node != NULL)
    {
        free(Node);
    }

}
/**
 * @brief Append a node to the end of the list.
 *
 * @param Head
 * @param NewNode
 */
void  DLL_AppendNode( Node** Head, Node* NewNode )
{
    if (Head == NULL || NewNode == NULL)
    {
        return;
    }

    if (*Head == NULL)
    {
        *Head = NewNode;
    }
    else
    {
        Node* Temp = *Head;
        while (Temp->NextNode != NULL)
        {
            Temp = Temp->NextNode;
        }
        Temp->NextNode = NewNode;
        NewNode->PrevNode = Temp;
    }
}
/**
 * @brief Insert a new node after the current node.
 *
 * @param Current
 * @param NewNode
 */
void  DLL_InsertAfter( Node* Current, Node* NewNode )
{
    if (Current == NULL || NewNode == NULL)
    {
        return;
    }

    NewNode->PrevNode = Current;
    NewNode->NextNode = Current->NextNode;

    if (Current->NextNode != NULL)
    {
        Current->NextNode->PrevNode = NewNode;
    }

    Current->NextNode = NewNode;
}
/**
 * @brief Remove a node from the list.
 *
 * @param Head
 * @param Remove
 */
void  DLL_RemoveNode( Node** Head, Node* Remove )
{
    if (Head == NULL || *Head == NULL || Remove == NULL)
    {
        return;
    }

    if (*Head == Remove)
    {
        *Head = Remove->NextNode;
    }

    if (Remove->PrevNode != NULL)
    {
        Remove->PrevNode->NextNode = Remove->NextNode;
    }

    if (Remove->NextNode != NULL)
    {
        Remove->NextNode->PrevNode = Remove->PrevNode;
    }
}
/**
 * @brief Get a node at a specific location.
 *
 * @param Head
 * @param Location
 * @return Node*
 */
Node* DLL_GetNodeAt( Node* Head, int Location )
{
    if (Head == NULL || Location < 0)
    {
        return NULL;
    }

    Node* Current = Head;
    int CurrentLocation = 0;

    while (Current != NULL)
    {
        if (CurrentLocation == Location)
        {
            return Current;
        }
        Current = Current->NextNode;
        CurrentLocation++;
    }

    return NULL;
}
int   DLL_GetNodeCount( Node* Head )
{
    int Count = 0;
    Node* Current = Head;

    while (Current != NULL)
    {
        Count++;
        Current = Current->NextNode;
    }

    return Count;
}