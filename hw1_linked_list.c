#include <stdio.h>
#include <stdlib.h>

typedef struct listItem 
{
  int someInteger;
  struct listItem* next;
} list_Item;

list_Item* deleteItem (list_Item* lead, int ridListOf);
void printLinkedList (list_Item* begin);
void sortLinkedList (list_Item* head);
list_Item* insert(list_Item* head, int addStuff);

int main () 
{
    list_Item* start = NULL;
    int remove = 0;
    int  addStuff = 0;
    char action = '\0';

    do 
    {  
        printf("Enter action ");
        printf("[i for insert, r for remove s for sort, q for quit]: ");
        scanf (" %c",&action);
        if (action == 'i') 
        {
            printf("Enter data to be inserted: ");
            scanf("%d",&addStuff);
            start = insert(start,addStuff); 
            printLinkedList(start);
        } 
        else  if (action == 'r') 
        {
            printf("Enter data to be removed: ");
            scanf("%d",&remove);
            start = deleteItem(start,remove);
            printLinkedList(start);
        }
        else if (action == 's') 
        {
            sortLinkedList(start);
            printLinkedList(start);
        } 
        else if (action == 'q') 
        {
            printf("Bye.\n");
        } 
        else 
        {  
            printf("Invalid Input.\n");
        }
  } while (action != 'q');
  return 0;
}

list_Item* deleteItem (list_Item* lead, int ridListOf) 
{
    list_Item* deletePtr = lead;
    list_Item* temp = lead;

    if (lead == NULL) 
    {
        printf("You can't delete anything from an empty list, dummy.\n");
        return lead;
    }
    else if (lead->someInteger == ridListOf) 
    {
        deletePtr = lead;
        lead = lead->next;
        free(deletePtr);
        return lead;
    } 
    else 
    {
        while (deletePtr != NULL && deletePtr->someInteger != ridListOf) 
        {
            temp = deletePtr;
            deletePtr = deletePtr->next;
	    }
        if(temp != NULL) 
        {
            temp->next = deletePtr->next;
            free(deletePtr); 
            return lead;
        } 
        else 
        {
            printf("Data not in list. \n");
            return lead;
        }
    }	    
}

void printLinkedList (list_Item* begin) 
{
    list_Item* traverseList = begin;

    printf("List is: ");
    if (begin == NULL)
        traverseList = NULL;
    else 
        while (traverseList != NULL) 
        {
	        if (traverseList->next == NULL) 
	            printf("%d\n", traverseList->someInteger);
	        else 
                printf("%d -> ", traverseList->someInteger);
	        traverseList = traverseList->next;
	    }
}

void sortLinkedList (list_Item* head) 
{
    list_Item* checkPtr = head;
    list_Item* trailPtr = head;
    int placeHolder = 0;
  
    while (checkPtr != NULL) 
    {
        if (checkPtr->someInteger < trailPtr->someInteger) 
        {
	        placeHolder = trailPtr->someInteger;
	        trailPtr->someInteger = checkPtr->someInteger;
	        checkPtr->someInteger = placeHolder;
	        checkPtr = trailPtr;
	    }
        checkPtr = checkPtr->next;
        if (checkPtr == NULL) 
        {
	        trailPtr = trailPtr->next;
	        checkPtr = trailPtr;
        }
    }
}

list_Item* insert(list_Item* head, int addStuff) 
{
    list_Item* temp = malloc(sizeof(list_Item));
    temp->someInteger = addStuff;
    temp->next = head;
    head = temp;
    return head;
}
