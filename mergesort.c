//
// Created by André Pinto on 11/12/17.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mergesort.h"


/* Function to insert a node at the beginging of the linked list */
void addElement(struct Node** list, char * new_data, int key)
{
    /* allocate node */
    struct Node* new_node =
            (struct Node*) malloc(sizeof(struct Node));

    new_node->data = (char *) malloc(sizeof(char) * strlen(new_data)+1);

    /* put in the data  */
    strcpy(new_node->data,new_data);
    new_node->id = key;

    if(key == 0){
        new_node->next = NULL;
    }
    else {
        /* link the old list off the new node */
        new_node->next = (*list);
    }

    /* move the head to point to the new node */
    (*list) = new_node;
}


/* Function to print nodes in a given linked list */
void printList(struct Node *node)
{
    while(node!=NULL)
    {
        printf("id -> %d %s\n",node->id, node->data);
        node = node->next;
    }
}

/* sorts the linked list by changing next pointers (not data) */
void MergeSort(struct Node** list, int flag)
{
    struct Node* aux = *list;
    struct Node* a;
    struct Node* b;

    /* Base case -- length 0 or 1 */
    if ((aux == NULL) || (aux->next == NULL))
    {
        return;
    }

    /* Split aux into 'a' and 'b' sublists */
    FrontBackSplit(aux, &a, &b);

    /* Recursively sort the sublists */
    MergeSort(&a, flag);
    MergeSort(&b, flag);

    /* answer = merge the two sorted lists together */
    *list = Merge(a, b, flag);
}

struct Node* Merge(struct Node *a, struct Node *b, int flag)
{
    struct Node* result = NULL;

    /* Base cases */
    if (a == NULL)
        return(b);
    else if (b==NULL)
        return(a);

    /* Pick either a or b, and recur */
    if(flag){
        if (strcmp(a->data,b->data) < 0) {
            result = a;
            result->next = Merge(a->next, b, flag);

        } else {
            result = b;
            result->next = Merge(a, b->next, flag);
        }
    } else {
        if (a->id < b->id) {
            result = a;
            result->next = Merge(a->next, b, flag);

        } else {
            result = b;
            result->next = Merge(a, b->next, flag);
        }
    }

    return(result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
     and return the two lists using the reference parameters.
     If the length is odd, the extra node should go in the front list.
     Uses the fast/slow pointer strategy.  */
void FrontBackSplit(struct Node* source,
                    struct Node** frontRef, struct Node** backRef)
{
    struct Node* fast;
    struct Node* slow;
    if (source==NULL || source->next==NULL)
    {
        /* length < 2 cases */
        *frontRef = source;
        *backRef = NULL;
    }
    else
    {
        slow = source;
        fast = source->next;

        /* Advance 'fast' two nodes, and advance 'slow' one node */
        while (fast != NULL)
        {
            fast = fast->next;
            if (fast != NULL)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }

        /* 'slow' is before the midpoint in the list, so split it in two
          at that point. */
        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}