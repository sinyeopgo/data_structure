/**
 * @file LCRSTree.c
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2025-10-12
 *
 * @copyright Copyright (c) 2025
 *
 */
/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include "LCRSTree.h"
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

LCRSNode* LCRS_CreateNode( ElementType NewData )
{
    LCRSNode* NewNode = (LCRSNode*)malloc(sizeof(LCRSNode));
    NewNode->LeftChild = NULL;
    NewNode->RightSibling = NULL;
    NewNode->Data = NewData;

    return NewNode;
}
void      LCRS_DestroyNode( LCRSNode* Node )
{
    free(Node);
}
void      LCRS_DestroyTree( LCRSNode* Root )
{
    if (Root == NULL)
        return;

    LCRS_DestroyTree(Root->LeftChild);
    LCRS_DestroyTree(Root->RightSibling);

    LCRS_DestroyNode(Root);
}

void      LCRS_AddChildNode( LCRSNode* ParentNode, LCRSNode *ChildNode)
{
    if (ParentNode == NULL || ChildNode == NULL)
        return;

    if (ParentNode->LeftChild == NULL)
    {
        ParentNode->LeftChild = ChildNode;
    }
    else
    {
        LCRSNode* Sibling = ParentNode->LeftChild;
        while (Sibling->RightSibling != NULL)
        {
            Sibling = Sibling->RightSibling;
        }
        Sibling->RightSibling = ChildNode;
    }
}
void      LCRS_PrintTree( LCRSNode* Node, int Depth )
{
    if (Node == NULL)
        return;

    for (int i = 0; i < Depth; i++)
    {
        printf("  ");
    }
    printf("%c\n", Node->Data);

    LCRS_PrintTree(Node->LeftChild, Depth + 1);
    LCRS_PrintTree(Node->RightSibling, Depth);
}
