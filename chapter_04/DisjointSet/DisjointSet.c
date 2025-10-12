/**
 * @file DisjointSet.c
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
#include "DisjointSet.h"
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
void DS_UnionSet( DisjointSet* Set1, DisjointSet* Set2 )
{
    DisjointSet* Root1 = DS_FindSet( Set1 );
    DisjointSet* Root2 = DS_FindSet( Set2 );

    if( Root1 == NULL || Root2 == NULL )
    {
        return;
    }

    if( Root1 != Root2 )
    {
        Root2->Parent = Root1;
    }
}
DisjointSet* DS_FindSet( DisjointSet* Set )
{
    if (Set == NULL)
    {
        return NULL;
    }
    if (Set->Parent != Set)
    {
        Set->Parent = DS_FindSet(Set->Parent);
    }
    return Set->Parent;
}
DisjointSet* DS_MakeSet( void* NewData )
{
    DisjointSet* NewSet = (DisjointSet*)malloc( sizeof( DisjointSet ) );
    if( NewSet == NULL )
    {
        return NULL;
    }

    NewSet->Parent = NewSet;
    NewSet->Data   = NewData;

    return NewSet;
}
void DS_DestroySet( DisjointSet* Set )
{
    if( Set != NULL )
    {
        free( Set );
    }
}
