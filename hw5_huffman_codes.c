#include <stdio.h>
#include <stdlib.h>

#define SIZE 47

typedef struct _huffman
{
  char token;
  int frequency;
  struct _huffman* leftChild;
  struct _huffman* rightChild;
} HUFFMAN;

void insertHeap(HUFFMAN* theHeap[SIZE], HUFFMAN* newNode, int count);
HUFFMAN* removeHeap(HUFFMAN* Heap[SIZE], int point);
void preorderRecursive(HUFFMAN* theRoot);
void inorderRecursive(HUFFMAN* Root);

int main()
{
    HUFFMAN* heap[SIZE] = { NULL };
    HUFFMAN* root = NULL;
    char character = '\0';
    int index = 0;

    while (character != '$')
    {
        printf("(enter a '$' to quit entering characters) ");
        scanf(" %c",&character);
        if (character != '$')
        {
            root = malloc(sizeof(HUFFMAN));
            root->token = character;
            printf("Enter '%c's frequency: ", character);
            scanf("%d", &(root->frequency));
            ++index;
            insertHeap(heap, root, index);
        }
    }

    while (heap[2] != NULL)
    {
        root = malloc(sizeof(HUFFMAN));
        root->token = '-';
        root->leftChild = removeHeap(heap,index); 
        index = index - 1;
        root->rightChild = removeHeap(heap,index);
        root->frequency = root->leftChild->frequency 
            + root->rightChild->frequency;
        insertHeap(heap,root,index);
    }

    printf("The nodes of the Huffman tree in In-order are: \n");
    inorderRecursive(root);
    printf("and in Pre-order are: \n");
    preorderRecursive(root);
    return 0;
}

void insertHeap(HUFFMAN* theHeap[SIZE], HUFFMAN* newNode, int count)
{
    HUFFMAN* tempNode = NULL;
    int parent = 0;
    theHeap[count] = newNode;
    parent = count / 2;
    while ((parent != 0) 
        && (theHeap[parent]->frequency > theHeap[count]->frequency))
    {
        tempNode = theHeap[parent];
        theHeap[parent] = theHeap[count];
        theHeap[count] = tempNode;
        count = parent;
        parent = count/2;
    }
}

HUFFMAN* removeHeap(HUFFMAN* Heap[SIZE], int point)
{                                    
    HUFFMAN* extract = NULL;
    HUFFMAN* extraNode = NULL;
    int left = 0;
    int right = 0;
    int complete = 0;
    extract = Heap[1];
    Heap[1] = Heap[point];
    Heap[point] = NULL;
    point = 1;
    left = 2 * point;
    right = 2 * point + 1;
    while (complete != 1)
    {
        if ((Heap[left] != NULL) && (Heap[right] != NULL))
        {
            if ((Heap[point]->frequency > Heap[right]->frequency) 
                || (Heap[point]->frequency > Heap[left]->frequency))
            {
                if (Heap[right]->frequency < Heap[left]->frequency)
                {
                    extraNode = Heap[point];
                    Heap[point] = Heap[right];
                    Heap[right] = extraNode;
                    point = right;
                }
                else
                {
                    extraNode = Heap[point];
                    Heap[point] = Heap[left]; 
                    Heap[left] = extraNode;
                    point = left;
                }
            }
            else
            {
                complete = 1;
            }
        }
        else if ((Heap[left] != NULL)
            && (Heap[left]->frequency < Heap[point]->frequency))
        {
            extraNode = Heap[point];
            Heap[point] = Heap[left];
            Heap[left] = extraNode;
            point = left;
        }
        else if ((Heap[right] != NULL)
            && (Heap[right]->frequency < Heap[point]->frequency))
        {
            extraNode = Heap[point];
            Heap[point] = Heap[right];
            Heap[right] = extraNode;
            point = right;
        }
        else
        {
            complete = 1;
        }
        left = 2 * point;
        right = 2 * point + 1;
    }
    return extract; 
}

void preorderRecursive(HUFFMAN* theRoot)
{
    if (theRoot != NULL)
    {
        printf("%c     %d\n",theRoot->token, theRoot->frequency);
        preorderRecursive(theRoot->leftChild);
        preorderRecursive(theRoot->rightChild);
    }  
}

void inorderRecursive(HUFFMAN* Root)
{
    if (Root != NULL)
    {
        inorderRecursive(Root->leftChild);
        printf("%c     %d\n", Root->token,Root->frequency);
        inorderRecursive(Root->rightChild);
    }
}
