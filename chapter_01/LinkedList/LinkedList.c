/**
 * @file LinkedList.c
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief Singly Linked List implementation
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
#include "LinkedList.h"
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
Node* SLL_CreateNode(ElementType NewData)
{
    Node* NewNode = (Node*)malloc(sizeof(Node));
    if (NewNode == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    NewNode->Data = NewData;
    NewNode->NextNode = NULL;
    return NewNode;
}
void  SLL_DestroyNode(Node* Node)
{
    if (Node != NULL)
    {
        free(Node);
    }
}
void  SLL_AppendNode(Node** Head, Node* NewNode)
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
    }
}
void  SLL_InsertAfter(Node* Current, Node* NewNode)
{
    if (Current == NULL || NewNode == NULL)
    {
        return;
    }

    NewNode->NextNode = Current->NextNode;
    Current->NextNode = NewNode;
}
void  SLL_InsertNewHead(Node** Head, Node* NewHead)
{
    if (Head == NULL || NewHead == NULL)
    {
        return;
    }

    NewHead->NextNode = *Head;
    *Head = NewHead;
}
void  SLL_RemoveNode(Node** Head, Node* Remove)
{
    if (Head == NULL || *Head == NULL || Remove == NULL)
    {
        return;
    }

    if (*Head == Remove)
    {
        *Head = Remove->NextNode;
    }
    else
    {
        Node* Temp = *Head;
        while (Temp != NULL && Temp->NextNode != Remove)
        {
            Temp = Temp->NextNode;
        }
        if (Temp != NULL)
        {
            Temp->NextNode = Remove->NextNode;
        }
    }
}
Node* SLL_GetNodeAt(Node* Head, int Location)
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
int   SLL_GetNodeCount(Node* Head)
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
