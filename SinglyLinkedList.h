/**
 * @brief     Implementation of a singly linked list in C
 * @author    Mo ( GITHUB: xMo-101, DISCORD: alexanderaugustus )
 * @date      21. July 2024
 * @version   1.0
 */

#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#define ERR_ALLOC "ERROR: Couldn't allocate memory!\n"
#define ERR_NULL "ERROR: Action failed in presence of (NULL) pointer!\n"

// Struct for nodes
typedef struct node {
    int value;
    struct node *next;
} node_t;

// Struct for linkedlists
typedef struct LinkedList {
    node_t *head;
    int size;
} linkedlist_t;

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ { # FUNCTIONS # } ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ { INSERTION } ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
void InsertAtHead(linkedlist_t *list, node_t *ToInsert);

void InsertAtTail(linkedlist_t *list, node_t *ToInsert);

void InsertAtPosition(const int position, linkedlist_t *list, node_t *ToInsert);

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ { CREATE } ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
node_t *CreateNode(const int data);

linkedlist_t *CreateList(const int size);

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ { DELETE } ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
void DeleteNodeByData(linkedlist_t *list, int data);

void DeleteNodeAtPosition(linkedlist_t *list, int position);

void DeleteHead(linkedlist_t *list);

void DeleteTail(linkedlist_t *list);

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ { CALCULATE } ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
int CalcListBytes(const linkedlist_t *list);

int CalcNodes(const linkedlist_t *list);

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ { OTHER } ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
void PrintLinkedList(const linkedlist_t *list);

void PrintLinkedListInfo(const linkedlist_t *list);

void freelist(linkedlist_t *list);

int IsEmpty(const linkedlist_t *list);

node_t *FindNodeByData(const linkedlist_t *list, int data);

void ReverseList(linkedlist_t *list);

#endif //SINGLYLINKEDLIST_H