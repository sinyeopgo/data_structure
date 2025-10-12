/**
 * @file ExpressionTree.c
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
#include "ExpressionTree.h"
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
ETNode*   ET_CreateNode( ElementType NewData )
{
    ETNode* NewNode = (ETNode*)malloc( sizeof( ETNode ) );
    if( NewNode == NULL )
    {
        fprintf( stderr, "Error: Memory allocation failed in ET_CreateNode()\n" );
        exit( EXIT_FAILURE );
    }

    NewNode->Data  = NewData;
    NewNode->Left  = NULL;
    NewNode->Right = NULL;

    return NewNode;
}
void      ET_DestroyNode( ETNode* Node )
{
    if( Node == NULL ) {
        return;
    }
    free(Node);
}
void      ET_DestroyTree( ETNode* Root )
{
    if ( Root == NULL )
        return;

    ET_DestroyTree( Root->Left );
    ET_DestroyTree( Root->Right );
    ET_DestroyNode( Root );
}

void      ET_PreorderPrintTree( ETNode* Node )
{
    if( Node == NULL )
        return;

    printf( "%c ", Node->Data );
    ET_PreorderPrintTree( Node->Left );
    ET_PreorderPrintTree( Node->Right );
}
void      ET_InorderPrintTree( ETNode* Node )
{
    if( Node == NULL )
        return;

    ET_InorderPrintTree( Node->Left );
    printf( "%c ", Node->Data );
    ET_InorderPrintTree( Node->Right );
}
void      ET_PostorderPrintTree( ETNode* Node )
{
    if( Node == NULL )
        return;

    ET_PostorderPrintTree( Node->Left );
    ET_PostorderPrintTree( Node->Right );
    printf( "%c ", Node->Data );
}
void      ET_BuildExpressionTree( char* PostfixExpression, ETNode** Node )
{
    int len = strlen( PostfixExpression );
    int   token = PostfixExpression[len - 1];
    PostfixExpression[len - 1] = '\0';

    switch(token)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        {
            ETNode* NewNode = ET_CreateNode( token );
            ET_BuildExpressionTree( PostfixExpression, &NewNode->Right );
            ET_BuildExpressionTree( PostfixExpression, &NewNode->Left );
            *Node = NewNode;
            break;
        }
        default:
        {
            ETNode* NewNode = ET_CreateNode( token );
            *Node = NewNode;
            break;
        }
    }
}
double    ET_Evaluate( ETNode* Tree )
{
    if( Tree == NULL )
    {
        fprintf( stderr, "Error: Null tree in ET_Evaluate()\n" );
        exit( EXIT_FAILURE );
    }

    switch( Tree->Data )
    {
        case '+':
            return ET_Evaluate( Tree->Left ) + ET_Evaluate( Tree->Right );
        case '-':
            return ET_Evaluate( Tree->Left ) - ET_Evaluate( Tree->Right );
        case '*':
            return ET_Evaluate( Tree->Left ) * ET_Evaluate( Tree->Right );
        case '/':
            return ET_Evaluate( Tree->Left ) / ET_Evaluate( Tree->Right );
        default:
            return (double)(Tree->Data - '0');
    }
}