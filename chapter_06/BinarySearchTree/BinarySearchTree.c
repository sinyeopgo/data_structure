/**
 * @file BinarySearchTree.c
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2025-10-28
 *
 * @copyright Copyright (c) 2025
 *
 */
/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include "BinarySearchTree.h"
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
BSTNode*  BST_CreateNode( ElementType NewData )
{
    BSTNode* NewNode = (BSTNode*)malloc( sizeof(BSTNode) );
    NewNode->Left = NULL;
    NewNode->Right = NULL;
    NewNode->Data = NewData;

    return NewNode;
}
void      BST_DestroyNode( BSTNode* Node )
{
    free( Node );
}
void      BST_DestroyTree( BSTNode* Tree )
{
    if( Tree == NULL )
        return;

    BST_DestroyTree( Tree->Left );
    BST_DestroyTree( Tree->Right );

    BST_DestroyNode( Tree );
}

BSTNode*  BST_SearchNode( BSTNode* Tree, ElementType Target )
{
    if( Tree == NULL )
        return NULL;

    if( Target == Tree->Data )
        return Tree;
    else if( Target < Tree->Data )
        return BST_SearchNode( Tree->Left, Target );
    else
        return BST_SearchNode( Tree->Right, Target );
}
BSTNode*  BST_SearchMinNode( BSTNode* Tree )
{
    if( Tree == NULL )
        return NULL;

    BSTNode* Current = Tree;
    while( Current->Left != NULL )
    {
        Current = Current->Left;
    }

    return Current;
}
void      BST_InsertNode( BSTNode* Tree, BSTNode *Child )
{
    if( Child->Data < Tree->Data )
    {
        if( Tree->Left == NULL )
        {
            Tree->Left = Child;
        }
        else
        {
            BST_InsertNode( Tree->Left, Child );
        }
    }
    else
    {
        if( Tree->Right == NULL )
        {
            Tree->Right = Child;
        }
        else
        {
            BST_InsertNode( Tree->Right, Child );
        }
    }
}
BSTNode*  BST_RemoveNode( BSTNode* Tree,BSTNode* Parent, ElementType Target )
{
    if( Tree == NULL )
        return NULL;

    if( Target < Tree->Data )
    {
        return BST_RemoveNode( Tree->Left, Tree, Target );
    }
    else if( Target > Tree->Data )
    {
        return BST_RemoveNode( Tree->Right, Tree, Target );
    }
    else
    {
        //  삭제할 노드 발견
        if( Tree->Left != NULL && Tree->Right != NULL )
        {
            //  자식이 둘 다 있는 경우
            BSTNode* MinNode = BST_SearchMinNode( Tree->Right );
            ElementType Temp = Tree->Data;
            Tree->Data = MinNode->Data;
            MinNode->Data = Temp;

            return BST_RemoveNode( Tree->Right, Tree, Temp );
        }
        else
        {
            //  자식이 하나이거나 없는 경우
            BSTNode* Child = NULL;
            if( Tree->Left != NULL )
                Child = Tree->Left;
            else
                Child = Tree->Right;

            if( Parent != NULL )
            {
                if( Parent->Left == Tree )
                    Parent->Left = Child;
                else
                    Parent->Right = Child;
            }

            return Tree;
        }
    }
}
void      BST_InorderPrintTree( BSTNode* Node )
{
    if( Node == NULL )
        return;

    BST_InorderPrintTree( Node->Left );
    printf( "%d ", Node->Data );
    BST_InorderPrintTree( Node->Right );
}