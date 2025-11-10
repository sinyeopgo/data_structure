/**
 * @file RedBlackTree.c
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
#include "RedBlackTree.h"
#include <string.h>
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
extern RBTNode* Nil;
/*------------------------------------------------------------------------------
------
------    Functions
------
------------------------------------------------------------------------------*/
void      RBT_DestroyTree( RBTNode* Tree )
{
    if ( Tree != NULL && Tree != Nil )
    {
        RBT_DestroyTree( Tree->Left );
        RBT_DestroyTree( Tree->Right );
        RBT_DestroyNode( Tree );
    }
}

RBTNode*  RBT_CreateNode( ElementType NewData )
{
    RBTNode* NewNode = (RBTNode*)malloc( sizeof(RBTNode) );

    if ( NewNode != NULL )
    {
        NewNode->Parent = NULL;
        NewNode->Left   = NULL;
        NewNode->Right  = NULL;
        NewNode->Color  = BLACK;
        NewNode->Data   = NewData;
    }

    return NewNode;
}
void      RBT_DestroyNode( RBTNode* Node )
{
    if ( Node != NULL )
    {
        free( Node );
    }
}

RBTNode*  RBT_SearchNode( RBTNode* Tree, ElementType Target )
{
    RBTNode* Current = Tree;

    while ( Current != NULL && Current != Nil )
    {
        if ( Target == Current->Data )
        {
            return Current;
        }
        else if ( Target < Current->Data )
        {
            Current = Current->Left;
        }
        else
        {
            Current = Current->Right;
        }
    }

    return NULL;
}
RBTNode*  RBT_SearchMinNode( RBTNode* Tree )
{
    RBTNode* Current = Tree;

    if ( Current == NULL )
    {
        return NULL;
    }

    while ( Current->Left != Nil )
    {
        Current = Current->Left;
    }

    return Current;
}
void      RBT_InsertNode( RBTNode** Tree, RBTNode *NewNode )
{
    RBT_InsertNodeHelper( Tree, NewNode );

    NewNode->Color = RED;
    NewNode->Left  = Nil;
    NewNode->Right = Nil;

    RBT_RebuildAfterInsert( Tree, NewNode );
}
void      RBT_InsertNodeHelper( RBTNode** Tree, RBTNode *NewNode )
{
    RBTNode* Current = *Tree;
    RBTNode* Parent  = NULL;

    while ( Current != NULL && Current != Nil )
    {
        Parent = Current;

        if ( NewNode->Data < Current->Data )
        {
            Current = Current->Left;
        }
        else
        {
            Current = Current->Right;
        }
    }

    NewNode->Parent = Parent;

    if ( Parent == NULL )
    {
        *Tree = NewNode;
    }
    else if ( NewNode->Data < Parent->Data )
    {
        Parent->Left = NewNode;
    }
    else
    {
        Parent->Right = NewNode;
    }

    NewNode->Left  = Nil;
    NewNode->Right = Nil;
    NewNode->Color = RED;
}
RBTNode*  RBT_RemoveNode( RBTNode** Root, ElementType Target )
{
    RBTNode* TargetNode = RBT_SearchNode( *Root, Target );
    RBTNode* NodeToFix  = NULL;
    RBTNode* Y          = NULL;
    RBTNode* X          = NULL;

    if ( TargetNode == NULL )
    {
        return NULL;
    }

    if ( TargetNode->Left == Nil || TargetNode->Right == Nil )
    {
        Y = TargetNode;
    }
    else
    {
        Y = RBT_SearchMinNode( TargetNode->Right );
    }

    if ( Y->Left != Nil )
    {
        X = Y->Left;
    }
    else
    {
        X = Y->Right;
    }

    X->Parent = Y->Parent;

    if ( Y->Parent == NULL )
    {
        *Root = X;
    }
    else if ( Y == Y->Parent->Left )
    {
        Y->Parent->Left = X;
    }
    else
    {
        Y->Parent->Right = X;
    }

    if ( Y != TargetNode )
    {
        TargetNode->Data = Y->Data;
    }

    if ( Y->Color == BLACK )
    {
        NodeToFix = X;
        RBT_RebuildAfterRemove( Root, NodeToFix );
    }

    return Y;
}
void      RBT_RebuildAfterInsert( RBTNode** Tree, RBTNode* NewNode )
{
    RBTNode* Parent = NULL;
    RBTNode* Grand  = NULL;
    RBTNode* Uncle  = NULL;

    while ( ( NewNode != *Tree ) && ( NewNode->Parent->Color == RED ) )
    {
        Parent = NewNode->Parent;
        Grand  = Parent->Parent;

        if ( Parent == Grand->Left )
        {
            Uncle = Grand->Right;

            if ( Uncle->Color == RED )
            {
                Parent->Color = BLACK;
                Uncle->Color  = BLACK;
                Grand->Color  = RED;
                NewNode       = Grand;
            }
            else
            {
                if ( NewNode == Parent->Right )
                {
                    RBT_RotateLeft( Tree, Parent );
                    NewNode = Parent;
                    Parent  = NewNode->Parent;
                }

                RBT_RotateRight( Tree, Grand );
                Parent->Color = BLACK;
                Grand->Color  = RED;
                NewNode       = Parent;
            }
        }
        else
        {
            Uncle = Grand->Left;

            if ( Uncle->Color == RED )
            {
                Parent->Color = BLACK;
                Uncle->Color  = BLACK;
                Grand->Color  = RED;
                NewNode       = Grand;
            }
            else
            {
                if ( NewNode == Parent->Left )
                {
                    RBT_RotateRight( Tree, Parent );
                    NewNode = Parent;
                    Parent  = NewNode->Parent;
                }

                RBT_RotateLeft( Tree, Grand );
                Parent->Color = BLACK;
                Grand->Color  = RED;
                NewNode       = Parent;
            }
        }
    }

    ( *Tree )->Color = BLACK;
}
void      RBT_RebuildAfterRemove( RBTNode** Root, RBTNode* X )
{
    RBTNode* Sibling = NULL;

    while ( ( X != *Root ) && ( X->Color == BLACK ) )
    {
        if ( X == X->Parent->Left )
        {
            Sibling = X->Parent->Right;

            if ( Sibling->Color == RED )
            {
                Sibling->Color = BLACK;
                X->Parent->Color = RED;
                RBT_RotateLeft( Root, X->Parent );
                Sibling = X->Parent->Right;
            }

            if ( ( Sibling->Left->Color == BLACK ) &&
                 ( Sibling->Right->Color == BLACK ) )
            {
                Sibling->Color = RED;
                X = X->Parent;
            }
            else
            {
                if ( Sibling->Right->Color == BLACK )
                {
                    Sibling->Left->Color  = BLACK;
                    Sibling->Color        = RED;
                    RBT_RotateRight( Root, Sibling );
                    Sibling = X->Parent->Right;
                }

                Sibling->Color        = X->Parent->Color;
                X->Parent->Color      = BLACK;
                Sibling->Right->Color = BLACK;
                RBT_RotateLeft( Root, X->Parent );
                X = *Root;
            }
        }
        else
        {
            Sibling = X->Parent->Left;

            if ( Sibling->Color == RED )
            {
                Sibling->Color = BLACK;
                X->Parent->Color = RED;
                RBT_RotateRight( Root, X->Parent );
                Sibling = X->Parent->Left;
            }

            if ( ( Sibling->Left->Color == BLACK ) &&
                 ( Sibling->Right->Color == BLACK ) )
            {
                Sibling->Color = RED;
                X = X->Parent;
            }
            else
            {
                if ( Sibling->Left->Color == BLACK )
                {
                    Sibling->Right->Color = BLACK;
                    Sibling->Color       = RED;
                    RBT_RotateLeft( Root, Sibling );
                    Sibling = X->Parent->Left;
                }

                Sibling->Color       = X->Parent->Color;
                X->Parent->Color     = BLACK;
                Sibling->Left->Color = BLACK;
                RBT_RotateRight( Root, X->Parent );
                X = *Root;
            }
        }
    }
}

void      RBT_PrintTree( RBTNode* Node, int Depth, int BlackCount )
{
    int i = 0;
    char c = 'X';
    int v = -1;
    char cnt[100];

     if( Node == NULL || Node == Nil ) {
        return;
     }

     if ( Node->Color == BLACK ) {
        BlackCount++;
     }

     if( Node->Parent != NULL) {
        v = Node->Parent->Data;

        if( Node->Parent->Left == Node ) {
            c = 'L';
        } else {
            c = 'R';
        }
     }

     if( Node->Left == Nil && Node->Right == Nil ) {
        snprintf( cnt, sizeof(cnt)-1, " --------- %d", BlackCount );
     } else {
        strncpy( cnt, "", sizeof(cnt));
     }

     for (i = 0; i < Depth; i++ ) {
        printf("    ");
     }
     printf("%d %s [%c,%d] %s\n", Node->Data,
            (Node->Color == RED) ? "RED" : "BLACK",
            c, v, cnt );
    RBT_PrintTree( Node->Left, Depth + 1, BlackCount );
    RBT_PrintTree( Node->Right, Depth + 1, BlackCount );
}
void      RBT_RotateLeft( RBTNode** Root, RBTNode* Parent )
{
    RBTNode* RightChild = Parent->Right;
    RBTNode* RightLeft  = RightChild->Left;

    Parent->Right = RightLeft;

    if ( RightLeft != Nil )
    {
        RightLeft->Parent = Parent;
    }

    RightChild->Parent = Parent->Parent;

    if ( Parent->Parent == NULL )
    {
        *Root = RightChild;
    }
    else if ( Parent == Parent->Parent->Left )
    {
        Parent->Parent->Left = RightChild;
    }
    else
    {
        Parent->Parent->Right = RightChild;
    }

    RightChild->Left = Parent;
    Parent->Parent   = RightChild;
}
void      RBT_RotateRight( RBTNode** Root, RBTNode* Parent )
{
    RBTNode* LeftChild  = Parent->Left;
    RBTNode* LeftRight  = LeftChild->Right;

    Parent->Left = LeftRight;

    if ( LeftRight != Nil )
    {
        LeftRight->Parent = Parent;
    }

    LeftChild->Parent = Parent->Parent;

    if ( Parent->Parent == NULL )
    {
        *Root = LeftChild;
    }
    else if ( Parent == Parent->Parent->Left )
    {
        Parent->Parent->Left = LeftChild;
    }
    else
    {
        Parent->Parent->Right = LeftChild;
    }

    LeftChild->Right = Parent;
    Parent->Parent   = LeftChild;
}