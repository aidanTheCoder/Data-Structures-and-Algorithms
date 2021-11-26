#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5

int addToQueue(int myQueue[MAXSIZE], int* start, int* finish);
int removeFromQueue(int theQueue[MAXSIZE], int* begin, int* end); 

int main()
{
    int queue[MAXSIZE] = {0};
    char action = '\0';
    int rear = -1;
    int front = 0; 
    do
    {
        printf("What do you want to do? \
               \n\r[i for insert, r for remove, q for quit] ");   
        scanf(" %c",&action);
        if (action == 'i') 
            rear = addToQueue(queue, &front, &rear);
        else if (action == 'r')
            front = removeFromQueue(queue, &front, &rear);
        else if (action == 'q') 
            printf("~$\n");
        else 
            printf("That's not a valid input.\n"); 
    } 
    while (action != 'q');
    return 0;
}

int addToQueue(int myQueue[MAXSIZE], int* start, int* finish)
{
    int addInt = 0; 
    if ((*start == 0) && (*finish == MAXSIZE - 1))
        printf("Can't insert, the array is full \n");
    else 
    {
        print("Enter an integer to be inserted into the queue: ");
        scanf("%d", &addInt);
        *finish = ((*finish) + 1) % MAXSIZE;
        myQueue[*finish] = addInt; 
    }
    return *finish;
}

int removeFromQueue(int theQueue[MAXSIZE], int* begin, int* end)
{
    if ((*begin == 0) && (*end == -1))
        printf("Cannot remove, the queue is empty\n");
    else if (theQueue[*begin] == theQueue[*end])
    {
        printf("%d removed from the queue\n",theQueue[*begin]);
        theQueue[*begin] = 0;
        *begin = 0;
        *end = -1;
    } 
    else 
    {
        printf("%d removed from queue\n",theQueue[*begin]);
        theQueue[*begin] = 0;
        *begin = ((*begin) + 1) % MAXSIZE;
    }
    return *begin;
}
