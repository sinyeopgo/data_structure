/**
 * @file BinaryTree.h
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2025-10-12
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef BINARY_TREE_H
#define BINARY_TREE_H
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

typedef struct tagSBTNode
{
    struct tagSBTNode* Left;
    struct tagSBTNode* Right;

    ElementType Data;
} SBTNode;
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
SBTNode*  SBT_CreateNode( ElementType NewData );
void      SBT_DestroyNode( SBTNode* Node );
void      SBT_DestroyTree( SBTNode* Root );

void      SBT_PreorderPrintTree( SBTNode* Node );
void      SBT_InorderPrintTree( SBTNode* Node );
void      SBT_PostorderPrintTree( SBTNode* Node );

#endif
