/**
 * @file LCRSTree.h
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2025-10-12
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef LCRS_TREE_H
#define LCRS_TREE_H
/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
/*------------------------------------------------------------------------------
------
------    Defines and Types
------
------------------------------------------------------------------------------*/
typedef char ElementType;

typedef struct tagLCRSNode
{
    struct tagLCRSNode* LeftChild;
    struct tagLCRSNode* RightSibling;

    ElementType Data;
} LCRSNode;
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
LCRSNode* LCRS_CreateNode( ElementType NewData );
void      LCRS_DestroyNode( LCRSNode* Node );
void      LCRS_DestroyTree( LCRSNode* Root );

void      LCRS_AddChildNode( LCRSNode* ParentNode, LCRSNode *ChildNode);
void      LCRS_PrintTree( LCRSNode* Node, int Depth );

#endif
