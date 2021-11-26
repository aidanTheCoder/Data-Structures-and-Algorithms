#include <stdio.h>
#include <stdlib.h>

typedef struct circleQueue
{
    char item;
    struct circleQueue *next;
} cir_Queue;

void push(cir_Queue** control);
void pop(cir_Queue** popper);

int main()
{
    cir_Queue* master = NULL;
    char action = '\0'; 
    do
    {
        printf("What Do you want to do? \
               \n\r [i for insert, r for remove, q for quit] ");
        scanf(" %c", &action);
        if (action == 'i')
            push(&master);
        else if (action == 'r')
            pop(&master);
        else if (action == 'q')
            printf("Bye. \n");
        else
            printf("That's not a valid input. \n");
    } 
    while (action != 'q');
    return 0;
}

void push(cir_Queue** control)
{
    cir_Queue* newNode = NULL;
    newNode = malloc(sizeof(cir_Queue));
    printf("Enter character to be inserted: ");
    scanf(" %c", &(newNode->item));
    if (*control == NULL)
    {
        (*control) = newNode;
        (*control)->next = (*control);
    } 
    else
    {
        newNode->next = (*control)->next;
        (*control)->next = newNode;
        (*control) = newNode;
    }
}

void pop(cir_Queue** popper)
{
    cir_Queue* sendToVoid = NULL;
    if (*popper == NULL)
        printf("Cannot remove, list is empty.\n"); 
    else if ((*popper)->next == *popper)
    {
        printf("Removing %c from list. \n", (*popper)->next->item);
        sendToVoid = *popper;
        *popper = NULL;
        free(sendToVoid);
    } 
    else 
    {
        printf("Removing %c from the list. \n", (*popper)->next->item);
        sendToVoid = (*popper)->next;
        (*popper)->next = sendToVoid->next;
        free(sendToVoid);
    }
}
