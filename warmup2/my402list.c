

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#include "cs402.h"

#include "my402list.h"

// This is the function to create an anchor which is used to reference the list... And this anchor is initialized by pointing its next and previous to itself
int My402ListInit(My402List* list) 
{
	list->anchor.next = list->anchor.prev = &list->anchor;
	list->anchor.obj = NULL;
	return 1;
}

//Function to find the length of the list
int  My402ListLength(My402List* list)
{
	return list->num_members;	
	
}
// Function to find if the list is empty it returns 1 if the list is empty and 0 if list is not wmpty
int  My402ListEmpty(My402List* list)
{
	if (list->anchor.next == &list->anchor)	
		return 1;
	return 0;
}


//Function to return the first element in the list

My402ListElem *My402ListFirst(My402List* list)
{
	if (My402ListEmpty(list) == 1)
		return NULL;
	return list->anchor.next;	
}
//Function to return the last element of the list

My402ListElem *My402ListLast(My402List* list)
{
	if(My402ListEmpty(list) == 1)
		return NULL;
	else 
		return list->anchor.prev;
		
}
// Function to return the next element to the current element
My402ListElem *My402ListNext(My402List* list, My402ListElem* elem)
{
	if(elem == My402ListLast(list))
		return NULL;
	return elem->next;// actually we need to return the next element 
}

// Function to return the previous elemtn in the list
My402ListElem *My402ListPrev(My402List* list, My402ListElem* elem)
{
	if(elem  == My402ListFirst(list))
		return NULL;
	return elem->prev;  // Not understading why therer is a list arguement passed to this function
}

//Function to append the a list, for this we create a list dynamically and assign links from the anchor
int  My402ListAppend(My402List* list, void* obj)
{	
	// Create a list element
	My402ListElem* elem = NULL;
	My402ListElem *elemptr = NULL;
	elemptr = My402ListLast(list);
	elem = (My402ListElem *)malloc(sizeof(My402ListElem));
	if (elem == NULL )
	{
		printf("OutOfMemory");
		exit(-1);
	}
	//list->num_members = list->num_members +1;
	elem->obj = obj;
	// Assign links to the anchor
	if (My402ListEmpty(list ) == 1)
	{
		list->anchor.prev = list->anchor.next = elem;
		elem->next = &list->anchor;
		elem->prev = &list->anchor;
		list->num_members = list->num_members +1;
	}

	else
	{
		// we have to traverse till the end of the loop and then add the links
		elemptr->next = elem;
		elem->next = &list->anchor;
		elem->prev = elemptr;
		list->anchor.prev = elem;
		list->num_members = list->num_members +1;
	}
	return 1;
	
}
// Function to add the node at the head just after the anchor
int My402ListPrepend(My402List* list, void* obj)
{	
	My402ListElem* elem = NULL;
	elem = (My402ListElem *)malloc(sizeof(My402ListElem));
	if (elem == NULL )
	{
		printf("OutOfMemory");
		exit(-1);
	}
	//list->num_members = list->num_members +1;
	elem->obj = obj;
	if (My402ListEmpty(list ) == 1)
	{
		list->anchor.prev = list->anchor.next = elem;
		elem->next = &list->anchor;
		elem->prev = &list->anchor;
list->num_members = list->num_members +1;
	}
	else
	{
		My402ListElem *first= list->anchor.next;
		list->anchor.next = elem;
		elem->prev = &list->anchor;
		elem->next=first;
	first->prev=elem;
//		My402ListElem* oldhead = My402ListNext(list,elem);
//		oldhead->prev = elem;
list->num_members = list->num_members +1;
	}	
	return 1;
}

void My402ListUnlink(My402List* list, My402ListElem* elem)
{
	My402ListElem* temp = NULL;
	My402ListElem* temp1 = NULL;
	if (list->num_members == 1)
	{
	
	list->anchor.next=list->anchor.prev=&list->anchor;		
	free(My402ListFirst(list));
		list->num_members = list->num_members -1 ;
		return ;
	}
	else if(elem->next == &list->anchor)
		{
			elem->prev->next = &list->anchor;
			list->anchor.prev = elem->prev;
			free(elem);
			list->num_members = list->num_members - 1;
			return ;

		}
	else
	{	
		temp = elem->prev;
temp1=elem->next; 
		temp->next=temp1;
temp1->prev=temp;
		free(elem);
		list->num_members = list->num_members - 1;
	}
}
void My402ListUnlinkAll(My402List* list)
{
	My402ListElem *elem=NULL;

        for (elem=My402ListFirst(list);elem !=&list->anchor;elem=My402ListNext(list, elem)){
		//free(elem);
		//list->num_members = list->num_members - 1;
		My402ListUnlink(list,elem);
        
	}
}


int My402ListInsertAfter(My402List* list, void* obj, My402ListElem* elem)
{
	if(elem == NULL)
	{	
		My402ListAppend(list,obj);
		return 1;
	}
	My402ListElem *newnext = elem->next;
	My402ListElem* newelem = NULL;
	newelem = (My402ListElem *)malloc(sizeof(My402ListElem));
	if (newelem == NULL )
	{
		printf("OutOfMemory");
		exit(-1);
	}
	list->num_members = list->num_members +1;
	newelem->obj = obj;
	newelem->next = newnext;
	newelem->prev=elem;
	newnext->prev = newelem;
	elem->next = newelem;
	
	return 1;
}
int  My402ListInsertBefore(My402List* list, void* obj, My402ListElem* elem)
{
	if(elem == NULL)
	{
		My402ListPrepend(list,obj);
		return 1;	
	}	
	My402ListElem *newprev = elem->prev;
	My402ListElem* newelem = NULL;
	newelem = (My402ListElem *)malloc(sizeof(My402ListElem));
	if (newelem == NULL )
	{
		printf("OutOfMemory");
		exit(-1);
	}
	list->num_members = list->num_members +1;
	newelem->obj = obj;
	newelem->next = elem;
	newelem->prev = newprev;

	newprev->next = newelem;
	elem->prev = newelem;
	
	return 1;
}

My402ListElem *My402ListFind(My402List* list, void* obj)
{
	My402ListElem *elem = NULL;
	for (elem=My402ListFirst(list);elem != NULL;elem=My402ListNext(list, elem)) 
	{
		if (elem->obj == obj)
			return elem;
	}
	return NULL;
}



