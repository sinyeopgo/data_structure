/**
 * @file ExpressionTree.h
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2025-10-12
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H
/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*------------------------------------------------------------------------------
------
------    Defines and Types
------
------------------------------------------------------------------------------*/
typedef char ElementType;

typedef struct tagETNode
{
    struct tagETNode* Left;
    struct tagETNode* Right;

    ElementType Data;
} ETNode;
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
ETNode*   ET_CreateNode( ElementType NewData );
void      ET_DestroyNode( ETNode* Node );
void      ET_DestroyTree( ETNode* Root );

void      ET_PreorderPrintTree( ETNode* Node );
void      ET_InorderPrintTree( ETNode* Node );
void      ET_PostorderPrintTree( ETNode* Node );
void      ET_BuildExpressionTree( char* PostfixExpression, ETNode** Node );
double    ET_Evaluate( ETNode* Tree );

#endif
