/**
 * @file QuickSort.c
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2025-10-21
 *
 * @copyright Copyright (c) 2025
 *
 */
/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include <stdio.h>
/*------------------------------------------------------------------------------
------
------    Defines and Types
------
------------------------------------------------------------------------------*/
#define STACK_MAX 100
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
void Swap( int* A, int* B )
{
    int Temp = *A;
    *A = *B;
    *B = Temp;
}

void MedianOfThree( int DataSet[], int Left, int Right )
{
    int Center = (Left + Right) / 2;

    if ( DataSet[Left] > DataSet[Center] )
        Swap( &DataSet[Left], &DataSet[Center] );

    if ( DataSet[Left] > DataSet[Right] )
        Swap( &DataSet[Left], &DataSet[Right] );

    if ( DataSet[Center] > DataSet[Right] )
        Swap( &DataSet[Center], &DataSet[Right] );

    Swap( &DataSet[Center], &DataSet[Left] );
}

int Partition( int DataSet[], int Left, int Right )
{
    MedianOfThree( DataSet, Left, Right );

    int First = Left;
    int Pivot = DataSet[First];

    ++Left;

    while( Left <= Right )
    {
        while( DataSet[Left] <= Pivot && Left < Right )
            ++Left;

        while( DataSet[Right] >= Pivot && Left <= Right )
            --Right;

        if ( Left < Right )
            Swap( &DataSet[Left], &DataSet[Right]);
        else
            break;
    }

    Swap( &DataSet[First], &DataSet[Right] );

    return Right;
}

void QuickSortIterative(int DataSet[], int Length)
{
    int Stack[STACK_MAX];
    int Top = -1;

    Stack[++Top] = 0;
    Stack[++Top] = Length - 1;

    while (Top >= 0)
    {
        int Right = Stack[Top--];
        int Left = Stack[Top--];

        int PivotIndex = Partition(DataSet, Left, Right);

        if (Left < PivotIndex - 1)
        {
            Stack[++Top] = Left;
            Stack[++Top] = PivotIndex - 1;
        }

        if (PivotIndex + 1 < Right)
        {
            Stack[++Top] = PivotIndex + 1;
            Stack[++Top] = Right;
        }

        if (Top >= STACK_MAX - 2) {
             printf("Warning: Stack limit reached. Increase STACK_MAX or ensure median selection is effective.\n");
             break;
        }
    }
}
void QuickSort(int DataSet[], int Left, int Right)
{
    if ( Left < Right )
    {
        int Index = Partition(DataSet, Left, Right);

        QuickSort( DataSet, Left, Index - 1 );
        QuickSort( DataSet, Index + 1, Right );
    }
}

int main( void )
{
    int DataSet[] = {6, 4, 2, 3, 1, 5};
    int Length = sizeof DataSet / sizeof DataSet[0];
    int i = 0;

    QuickSortIterative( DataSet, Length );
    // QuickSort( DataSet, 0, Length - 1 );

    for ( i=0; i<Length; i++ )
    {
        printf("%d ", DataSet[i]);
    }

    printf("\n");

    return 0;
}
