#include <stdio.h>
#include <stdlib.h>

typedef struct _binaryTree
{
    char keyValue;
    char string[11];
    struct _binaryTree* leftChild;
    struct _binaryTree* rightChild;
} TREENODE;

typedef struct _treeStack
{
    TREENODE* root;
    struct _treeStack* next;
} ROOTS;

#define ARRAY 11

TREENODE* addChildren(TREENODE* treeTop, char newDatum,
                      char code[ARRAY]);
int preOrderTraversal(TREENODE* topOfTree);
int inOrderTraversal(TREENODE* topTree);
TREENODE* searchNode(char node, TREENODE *start);
ROOTS* push(TREENODE *save, ROOTS * topOfStack);
TREENODE* pop(ROOTS ** stackAddress);

int main()
{
    TREENODE* root = NULL;
    TREENODE* findNode = NULL;
    char action = '\0'; 
    char addDatum = '\0';
    char searchFor = '\0'; 
    char message[ARRAY] = { '\0' };
    do
    {
        printf("[i for insert, f for find, q for quit] \
                \n\rEnter action: ");
        scanf(" %c", &action);
        if(action == 'i')
        {
            printf("Enter new nodes's key value: ");
            scanf(" %c", &addDatum);
            printf("Enter a string of up to 10 characters for %c: ",
                   addDatum);
            scanf("%s", message);
            root = addChildren(root, addDatum, message);
            printf("\nPre-order traversal: ");
            preOrderTraversal(root);
            printf("\nInorder traversal: ");
            inOrderTraversal(root);
        } 
        else if(action == 'f')
        {
            printf("Enter search key: ");
            scanf(" %c", &searchFor);
            findNode = searchNode(searchFor, root);
            if (findNode != NULL)
                printf("Found the string '%s' there. \n", 
                       findNode->string);
            else
                printf("'%c' not in the tree \n", searchFor);
        } 
        else if (action == 'q')
            printf("Bye.\n");
        else
            printf("Invalid Input \n");  
        
    } 
    while (action != 'q');
    return 0;
}

TREENODE* addChildren(TREENODE* treeTop, char newDatum,
                      char code[ARRAY])
{
    TREENODE* newChild = NULL;
    TREENODE* trvTree = treeTop;
    int index = 0;
    newChild = malloc(sizeof(TREENODE));
    newChild->keyValue = newDatum;
    for(index = 0; index < ARRAY; ++index)
        newChild->string[index] = code[index];
    if (treeTop == NULL)
        treeTop = newChild;
    else 
        while (trvTree != NULL)
           if((newChild->keyValue < trvTree->keyValue) 
              && (trvTree->leftChild == NULL))
           {
               trvTree->leftChild = newChild;
               trvTree = NULL;
           } 
           else if((newChild->keyValue > trvTree->keyValue) 
                   && (trvTree->rightChild == NULL))
           {
               trvTree->rightChild = newChild;
               trvTree = NULL;
           } 
           else if((newChild->keyValue < trvTree->keyValue) 
                   && (trvTree->leftChild != NULL))
               trvTree = trvTree->leftChild;
           else if((newChild->keyValue > trvTree->keyValue) 
                   && (trvTree->rightChild != NULL))
               trvTree = trvTree->rightChild;
           else
           {
               printf("Key value is already assigned node\n");
               trvTree = NULL;
           }
    return treeTop;
}

int preOrderTraversal(TREENODE *topOfTree)
{
    TREENODE* traverse = topOfTree;
    ROOTS* findStack = NULL;
    int complete = 0;
    while(complete != 1)
    {
        while(traverse != NULL)
        {
            printf("%c ",traverse->keyValue);            
            if(traverse->leftChild != NULL)
            {
                findStack = push(traverse,findStack);
                traverse = traverse->leftChild;
            } 
            else
            {
                traverse = traverse->rightChild;
            }
        }
        traverse = pop(&findStack);
        if (traverse == NULL)
            complete = 1;
        else
            traverse = traverse->rightChild;
    }
    return 1;
}

int inOrderTraversal(TREENODE* topTree)
{
    TREENODE* travel = topTree;
    ROOTS* stackTop = NULL;
    int finished = 0;
    while (finished != 1)
    {
        while(travel != NULL)
        {
            if(travel->leftChild != NULL)
            {
                stackTop = push(travel,stackTop);
                travel = travel->leftChild;
            } 
            else 
            {
                printf("%c ",travel->keyValue);
                travel = travel->rightChild;
            }
        }
        travel = pop(&stackTop);
        if (travel == NULL)
            finished = 1;
        else
        {
            printf("%c ",travel->keyValue);
            travel = travel->rightChild;
        }
    }
    return finished;
} 

TREENODE* searchNode(char node, TREENODE* start)
{
    TREENODE* traverse = start;
    while (traverse != NULL)
        if (node == traverse->keyValue)
            return traverse;
        else if (node < traverse->keyValue)
            traverse = traverse->leftChild;
        else
            traverse = traverse->rightChild;
    return NULL;
}

ROOTS* push(TREENODE* save, ROOTS* topOfStack)
{
    ROOTS* newRoot = NULL;
    newRoot = malloc(sizeof(ROOTS));
    newRoot->root = save;
    newRoot->next = topOfStack;
    topOfStack = newRoot;
    return topOfStack;
}

TREENODE* pop(ROOTS** stackAddress)
{
    TREENODE* extract = NULL;
    if (*stackAddress == NULL)  
        return NULL;
    else
    {
        extract = (*stackAddress)->root;
        *stackAddress = (*stackAddress)->next;   
        return extract;
    }
}
