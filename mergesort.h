//
// Created by swepp on 29/12/2018.
//

#ifndef PROJECT2018_MERGESORT_H
#define PROJECT2018_MERGESORT_H

/* Link list node */
struct Node
{
    char * data;
    int id;
    struct Node* next;
};

/* function prototypes */
struct Node* Merge(struct Node *a, struct Node *b, int flag);
void FrontBackSplit(struct Node* source,
                    struct Node** frontRef, struct Node** backRef);
void printList(struct Node *node);
void MergeSort(struct Node** list, int flag);
void addElement(struct Node** list, char * new_data, int key);
void init_NULL(struct Node*n);

#endif //PROJECT2018_MERGESORT_H