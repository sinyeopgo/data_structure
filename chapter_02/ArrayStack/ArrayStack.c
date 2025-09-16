/**
 * @file ArrayStack.c
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2025-09-02
 *
 * @copyright Copyright (c) 2025
 *
 */
/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include "ArrayStack.h"
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
void        AS_CreateStack(ArrayStack** Stack, int Capacity)
{
	if ( Capacity <= 0 )
		return;

	*Stack = (ArrayStack*)malloc( sizeof(ArrayStack) );
	if ( *Stack == NULL )
		return;

	(*Stack)->Capacity = Capacity;
	(*Stack)->Top      = -1;
	(*Stack)->Nodes    = (Node*)malloc( sizeof(Node) * Capacity );
	if ( (*Stack)->Nodes == NULL )
	{
		free( *Stack );
		*Stack = NULL;
		return;
	}
}
void        AS_DestroyStack(ArrayStack* Stack)
{
	if ( Stack == NULL )
		return;

	free( Stack->Nodes );
	free( Stack );
}
void        AS_Push(ArrayStack* Stack, ElementType Data)
{
	if ( Stack == NULL )
		return;

	if ( Stack->Top + 1 >= Stack->Capacity )
		return;

	Stack->Top++;
	Stack->Nodes[Stack->Top].Data = Data;
}
ElementType AS_Pop(ArrayStack* Stack)
{
	if ( Stack == NULL )
		return (ElementType){0};

	if ( Stack->Top < 0 )
		return (ElementType){0};

	return Stack->Nodes[Stack->Top--].Data;
}
ElementType AS_Top(ArrayStack* Stack)
{
	if ( Stack == NULL )
		return (ElementType){0};

	if ( Stack->Top < 0 )
		return (ElementType){0};

	return Stack->Nodes[Stack->Top].Data;
}
int         AS_GetSize(ArrayStack* Stack)
{
	if ( Stack == NULL )
		return 0;

	return Stack->Top + 1;
}
int         AS_IsEmpty(ArrayStack* Stack)
{
	if ( Stack == NULL )
		return 1;

	return Stack->Top < 0;
}