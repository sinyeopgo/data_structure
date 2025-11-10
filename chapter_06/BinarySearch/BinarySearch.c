#include <stdlib.h>
#include <stdio.h>
#include "Point.h"

Point* BinarySearch( Point PointList[], int Size, double Target )
{
    int Low = 0;
    int High = Size - 1;

    while( Low <= High )
    {
        int Mid = ( Low + High ) / 2;

        if( PointList[Mid].point == Target ) {
            return &PointList[Mid];
        } else if( PointList[Mid].point < Target ) {
            Low = Mid + 1;
        } else {
            High = Mid - 1;
        }
    }

    return NULL;
}

int ComparePoint( const void *_elem1, const void *_elem2 )
{
    Point* p1 = (Point*)_elem1;
    Point* p2 = (Point*)_elem2;

    if( p1->point < p2->point )
    {
        return -1;
    }
    else if( p1->point > p2->point )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main( void )
{
    int Length = sizeof DataSet / sizeof DataSet[0];
    Point* found = NULL;

    //  구매포인트에 대해 오름차순으로 정렬
    qsort( (void*)DataSet, Length, sizeof (Point), ComparePoint );

    //  구매포인트가 671.78점인 고객 찾기
    found = BinarySearch( DataSet, Length, 671.78 );

    printf("found... ID: %d, Point: %f \n", found->id, found->point );

    return 0;
}
