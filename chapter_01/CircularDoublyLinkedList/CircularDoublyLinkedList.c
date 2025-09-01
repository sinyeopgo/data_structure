/**
 * @file CircularDoublyLinkedList.c
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief Circular Doubly Linked List implementation
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
#include "CircularDoublyLinkedList.h"
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
Node* CDLL_CreateNode(ElementType NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));
	if (NewNode == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	NewNode->Data = NewData;
	NewNode->PrevNode = NewNode;
	NewNode->NextNode = NewNode;
	return NewNode;
}
/**
 * @brief Destroy a node.
 *
 * @param Node
 */
void  CDLL_DestroyNode(Node* Node)
{
	if (Node != NULL)
	{
		free(Node);
	}
}
/**
 * @brief Append a new node to the end of the list.
 *
 * @param Head
 * @param NewNode
 */
void  CDLL_AppendNode(Node** Head, Node* NewNode)
{
	if (Head == NULL || NewNode == NULL)
	{
		return;
	}

	if (*Head == NULL)
	{
		*Head = NewNode;
		NewNode->NextNode = NewNode;
		NewNode->PrevNode = NewNode;
	}
	else
	{
		Node* Tail = (*Head)->PrevNode;

		Tail->NextNode = NewNode;
		NewNode->PrevNode = Tail;
		NewNode->NextNode = *Head;
		(*Head)->PrevNode = NewNode;
	}
}
/**
 * @brief Insert a new node after the current node.
 *
 * @param Current
 * @param NewNode
 */
void  CDLL_InsertAfter(Node* Current, Node* NewNode)
{
	if (Current == NULL || NewNode == NULL)
	{
		return;
	}

	NewNode->NextNode = Current->NextNode;
	NewNode->PrevNode = Current;
	Current->NextNode->PrevNode = NewNode;
	Current->NextNode = NewNode;
}
/**
 * @brief Remove a node from the list.
 *
 * @param Head
 * @param Remove
 */
void  CDLL_RemoveNode(Node** Head, Node* Remove)
{
	if (Head == NULL || *Head == NULL || Remove == NULL)
	{
		return;
	}

	if (Remove->NextNode == Remove && Remove->PrevNode == Remove)
	{
		*Head = NULL;
	}
	else
	{
		Remove->PrevNode->NextNode = Remove->NextNode;
		Remove->NextNode->PrevNode = Remove->PrevNode;

		if (*Head == Remove)
		{
			*Head = Remove->NextNode;
		}
	}
}
/**
 * @brief Get a node at a specific location.
 *
 * @param Head
 * @param Location
 * @return Node*
 */
Node* CDLL_GetNodeAt(Node* Head, int Location)
{
	if (Head == NULL || Location < 0)
	{
		return NULL;
	}

	Node* Current = Head;
	int Count = 0;

	do
	{
		if (Count == Location)
		{
			return Current;
		}
		Current = Current->NextNode;
		Count++;
	} while (Current != Head);

	return NULL;
}
/**
 * @brief Get the count of nodes in the list.
 *
 * @param Head
 * @return int
 */
int   CDLL_GetNodeCount(Node* Head)
{
	if (Head == NULL)
	{
		return 0;
	}

	Node* Current = Head;
	int Count = 0;

	do
	{
		Count++;
		Current = Current->NextNode;
	} while (Current != Head);

	return Count;
}