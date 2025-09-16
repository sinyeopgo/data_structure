/**
 * @file Calculator.c
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2025-09-04
 *
 * @copyright Copyright (c) 2025
 *
 */
/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include "Calculator.h"
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
#define TRUE  1
#define FALSE 0
/*------------------------------------------------------------------------------
------
------    variables(external)
------
------------------------------------------------------------------------------*/
int number[11] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9','.' };
/*------------------------------------------------------------------------------
------
------    Functions
------
------------------------------------------------------------------------------*/
int          IsNumber( char Cipher )
{
    for ( int i = 0; i < 11; i++ )
    {
        if ( Cipher == number[i] )
            return TRUE;
    }

    return FALSE;
}
unsigned int GetNextToken( char* Expression, char* Token, int* TYPE )
{
    unsigned int i = 0;

    if ( Expression == NULL || Token == NULL || TYPE == NULL )
        return 0;

    while ( Expression[i] != '\0' && Expression[i] == SPACE )
        i++;

    if ( Expression[i] == '\0' )
        return 0;

    if ( IsNumber( Expression[i] ) )
    {
        *TYPE = OPERAND;
        unsigned int j = 0;
        while( IsNumber( Expression[i] ))
        {
            Token[j++] = Expression[i++];
        }
        Token[j] = '\0';
    }
    else
    {
        *TYPE = Expression[i];
        Token[0] = Expression[i++];
        Token[1] = '\0';
    }
    return i;
}
int          IsPrior( char Operator1, char Operator2 )
{
    int Priority1 = 0;
    int Priority2 = 0;

    switch ( Operator1 )
    {
        case PLUS:
        case MINUS:
            Priority1 = 1;
            break;

        case MULTIPLY:
        case DIVIDE:
            Priority1 = 2;
            break;
        default:
            Priority1 = 0;
            break;
    }

    switch ( Operator2 )
    {
        case PLUS:
        case MINUS:
            Priority2 = 1;
            break;

        case MULTIPLY:
        case DIVIDE:
            Priority2 = 2;
            break;
        default:
            Priority2 = 0;
            break;
    }

    return ( Priority1 >= Priority2 ) ? TRUE : FALSE;
}
void         GetPostfix( char* InfixExpression, char* PostfixExpression )
{
    LinkedListStack* OperatorStack;
    char             Token[20];
    int              TYPE;
    unsigned int     i = 0;
    unsigned int     j = 0;
    unsigned int     Length;

    if ( InfixExpression == NULL || PostfixExpression == NULL )
        return;

    LLS_CreateStack( &OperatorStack );

    Length = strlen( InfixExpression );

    while ( i < Length )
    {
        i += GetNextToken( &InfixExpression[i], Token, &TYPE );

        switch ( TYPE )
        {
            case OPERAND:
                j += sprintf( &PostfixExpression[j], "%s ", Token );
                break;

            case LEFT_PARENTHESIS:
                LLS_Push( OperatorStack, LLS_CreateNode( Token ) );
                break;

            case RIGHT_PARENTHESIS:
                while ( LLS_IsEmpty( OperatorStack ) == FALSE &&
                        LLS_Top( OperatorStack )->Data[0] != LEFT_PARENTHESIS )
                {
                    j += sprintf( &PostfixExpression[j], "%s",
                                  LLS_Top( OperatorStack )->Data );
                    LLS_DestroyNode( LLS_Pop( OperatorStack ) );
                }

                if ( LLS_IsEmpty( OperatorStack ) == FALSE &&
                     LLS_Top( OperatorStack )->Data[0] == LEFT_PARENTHESIS )
                {
                    LLS_DestroyNode( LLS_Pop( OperatorStack ) );
                }
                break;

            case PLUS:
            case MINUS:
            case MULTIPLY:
            case DIVIDE:
                while ( LLS_IsEmpty( OperatorStack ) == FALSE &&
                        LLS_Top( OperatorStack )->Data[0] != LEFT_PARENTHESIS &&
                        IsPrior( LLS_Top( OperatorStack )->Data[0], TYPE ) )
                {
                    j += sprintf( &PostfixExpression[j], "%s",
                                  LLS_Top( OperatorStack )->Data );
                    LLS_DestroyNode( LLS_Pop( OperatorStack ) );
                }

                LLS_Push( OperatorStack, LLS_CreateNode( Token ) );
                break;

            default:
                break;
        }
    }

    while ( LLS_IsEmpty( OperatorStack ) == FALSE )
    {
        j += sprintf( &PostfixExpression[j], "%s",
                      LLS_Top( OperatorStack )->Data );
        LLS_DestroyNode( LLS_Pop( OperatorStack ) );
    }
}
double       Calculate( char* PostfixExpression )
{
    LinkedListStack* OperandStack;
    char             Token[20];
    int              TYPE;
    unsigned int     i = 0;
    unsigned int     Length;

    if ( PostfixExpression == NULL )
        return 0.0;

    LLS_CreateStack( &OperandStack );

    Length = strlen( PostfixExpression );

    while ( i < Length )
    {
        i += GetNextToken( &PostfixExpression[i], Token, &TYPE );
        switch ( TYPE )
        {
            case OPERAND:
                LLS_Push( OperandStack, LLS_CreateNode( Token ) );
                break;

            case PLUS:
            case MINUS:
            case MULTIPLY:
            case DIVIDE:
            {
                Node* Operand2 = LLS_Pop( OperandStack );
                Node* Operand1 = LLS_Pop( OperandStack );

                if ( Operand1 == NULL || Operand2 == NULL )
                {
                    if ( Operand1 != NULL )
                        LLS_DestroyNode( Operand1 );

                    if ( Operand2 != NULL )
                        LLS_DestroyNode( Operand2 );

                    LLS_DestroyStack( OperandStack );
                    return 0.0;
                }

                double Value1 = atof( Operand1->Data );
                double Value2 = atof( Operand2->Data );
                double Result = 0.0;

                switch ( TYPE )
                {
                    case PLUS:
                        Result = Value1 + Value2;
                        break;

                    case MINUS:
                        Result = Value1 - Value2;
                        break;

                    case MULTIPLY:
                        Result = Value1 * Value2;
                        break;

                    case DIVIDE:
                        Result = Value1 / Value2;
                        break;

                    default:
                        break;
                }

                char ResultString[20];
                sprintf( ResultString, "%f", Result );

                LLS_Push( OperandStack, LLS_CreateNode( ResultString ) );

                LLS_DestroyNode( Operand1 );
                LLS_DestroyNode( Operand2 );
                break;
            }

            default:
                break;
        }
    }
    printf("TOP : %s\n", LLS_Top( OperandStack )->Data);
    double FinalResult = 0.0;

    if ( LLS_IsEmpty( OperandStack ) == FALSE )
    {
        Node* FinalNode = LLS_Pop( OperandStack );
        FinalResult = atof( FinalNode->Data );
        LLS_DestroyNode( FinalNode );
    }

    LLS_DestroyStack( OperandStack );
    return FinalResult;
}