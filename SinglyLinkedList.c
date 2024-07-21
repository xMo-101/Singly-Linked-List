/**
 * @brief       Implementation of a singly linked list in C
 * @author      Mo ( GITHUB: xMo-101, DISCORD: alexanderaugustus )
 * @date        21. July 2024
 * @version     1.0
 */

#include "SinglyLinkedList.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Creates node with a pointer to the next node and data of the 'int' type.
 * @param data the data to store in this node
 * @return node_t*
 */
node_t* CreateNode(const int data) {
    node_t* tmp = malloc(sizeof(node_t));
    if (NULL == tmp) { // If 'tmp' is still NULL then memory wasn't properly allocated.
        printf("%s", ERR_ALLOC);
        return NULL;
    }

    tmp->value = data; // assign the data
    tmp->next = NULL;  // init the next pointer to (NULL)
    return tmp;
}

/**
 * @brief Inserts a node to the front of a linked list.
 * @param list linked list
 * @param ToInsert node to insert at head
 */
void InsertAtHead(linkedlist_t* list, node_t* ToInsert) {
    if (NULL == ToInsert) {
        printf("%s", ERR_NULL);
        return;
    }
    // Insert 'ToInsert' at head:
    ToInsert->next = list->head; // Place 'ToInsert' in front of current head
    list->head = ToInsert; // Make 'ToInsert' the new head
    list->size++; // Increment the size of the linked list
}

/**
 * @brief Prints a linked list.
 * @param list the list to print
 */
void PrintLinkedList(const linkedlist_t* list) {
    if (NULL == list) { // handle error
        printf("%s", ERR_NULL);
        return;
    }
    for (node_t* node = list->head; node != NULL; node = node->next) {
        printf("%i ~ ", node->value);
    }
    printf("( END )\n");
}

/**
 * @brief Prints how many nodes a list has and how much space its using.
 * @param list the list you want the info of
 */
void PrintLinkedListInfo(const linkedlist_t* list) {
    if (NULL == list) { // handle error
        printf("%s", ERR_NULL);
        return;
    }
    printf(
        "This list contains %i nodes.\n"
        "This list takes up %i Bytes of storage space.\n",
        list->size, CalcListBytes(list)
    );
}

/**
 * @brief Inserts a node at the end of a linked list.
 * @param list the list to insert the node in
 * @param ToInsert the node to insert
 */
void InsertAtTail(linkedlist_t* list, node_t* ToInsert) {
    InsertAtPosition(list->size, list, ToInsert);
}

/**
 * @brief Calculates the amount of memory a list is taking up in bytes.
 * @param list the list to calculate the bytes of
 * @return # bytes
 */
int CalcListBytes(const linkedlist_t* list) {
    if (NULL == list) return 0; // If linked list is empty, then it has 0 bytes.
    int totalsize = sizeof(linkedlist_t); // get bytes of linkedlist_t
    return totalsize + sizeof(node_t) * list->size; // get total size (cuz of individual nodes) and return
}

/**
 * @brief Calculates the amount of nodes found inside of a linked list.
 * @param list the list to calculate the nodes of
 * @return # nodes
 */
int CalcNodes(const linkedlist_t* list) {
    if (NULL == list || NULL == list->head) return 0; // If linked list is empty, then it has 0 nodes.
    node_t* tmp = list->head;
    int NumNodes = 1; // By this point we know that the linked list has atleast 1 node.

    while ( tmp->next != NULL ) { // Increment 'NumNodes' until we reach the end of the linked list
        NumNodes++;
        tmp = tmp->next;
    }
    return NumNodes; // return result
}

/**
 * @brief Frees a linked list to prevent memory leak.
 * @param list the list to free
 */
void freelist(linkedlist_t *list) {
    if (NULL == list || NULL == list->head) return;
    node_t* current = list->head;
    node_t* next = NULL;

    while (current != NULL) {
        next = current->next;   // Save pointer to next node
        free(current);  // free current node
        current = next; // move to next node
    }
    // list->head = NULL; // reset head to NULL
    // list->size = 0;
    // free(list);
}

/**
 * @brief Inserts a node at a specific location in a linked list
 * @param position the position to insert at
 * @param list the list to insert in
 * @param ToInsert the node to insert
 */
void InsertAtPosition(const int position, linkedlist_t* list, node_t* ToInsert) {
    if (NULL == ToInsert || position < 0 || NULL == list) {
        return;
    }

    if (position == 0) { // if the position is 0, we can just insert at the head.
        InsertAtHead(list, ToInsert);
        return; // exit
    }

    if (position > list->size) { // If the position given is greater than the size of the list, insert at tail instead
        InsertAtTail(list, ToInsert);
        return; // exit
    }

    node_t* previous = NULL; // variable to keep track of previous node
    node_t* current = list->head; // variable to keep track of current node

    for (int curr = 0; curr < position && current != NULL; curr++) { // Traverse to the desired position
        previous = current;
        current = current->next;
    }

    // If position is greater than the length of the list
    if (previous == NULL) {
        return;  // Just return or handle as an error
    }

    // Insert the new node between previous and current
    previous->next = ToInsert;
    ToInsert->next = current;
    list->size++;
}

/**
 * @brief Finds a node by inspecting data.
 * @param list the list where the node is located
 * @param data the data to search for
 * @return node_t*
 */
node_t* FindNodeByData(const linkedlist_t* list, int data) {
    if (NULL == list || data == 0) {
        printf("%s", ERR_NULL);
        return NULL;
    }

    node_t* tmp = list->head; // temporary node for traversal

    while (tmp->value != data && NULL != tmp) { // traverse list until value of tmp is the sought data
        tmp = tmp->next;
    }

    return tmp->value == data ? tmp : NULL; // return pointer to found node or NULL if not node was not found
}

/**
 * @brief Deletes the head node of a list.
 * @param list the list to delete the head of
 */
void DeleteHead(linkedlist_t* list) {
    if (IsEmpty(list)) { // handle error
        printf("%s", ERR_NULL);
    }
    node_t* del = list->head; // store the head node in a temporary variable
    list->head = list->head->next; // move the head to the next node
    free(del); // free the to be deleted node
    list->size--; // decrement the size of the list
}

/**
 * @brief Deletes a node based off of its data.
 * @param list the list to delete the node in
 * @param data the data of the node you want to delete
 */
void DeleteNodeByData(linkedlist_t* list, int data) {
    if ( IsEmpty(list) ) { // handle error
        printf("%s", ERR_NULL);
        return;
    }

    // Handle deletion of head node separately
    if (list->head->value == data) {
        DeleteHead(list);
        return;
    }

    node_t* tmp = list->head; // temporary node for traversal
    while (tmp->next != NULL && tmp->next->value != data) { // traverse list until value of tmp is the sought data
        tmp = tmp->next;
    }

    // If we found the node just before the one to delete
    if (tmp->next != NULL) {
        node_t* del = tmp->next;
        tmp->next = del->next; // Remove the node from the list
        free(del); // Free the deleted node
        list->size--; // Decrement the list size
    }
}

/**
 * @brief Deletes a node based off of its position.
 * @param list the list to delete the node in
 * @param position the position of the node you want to delete
 */
void DeleteNodeAtPosition(linkedlist_t* list, int position) {
    if (position < 0 || IsEmpty(list)) { // handle error
        printf("%s", ERR_NULL);
        return; // exit
    }
    if (position == 0) {
        DeleteHead(list); // If the position is 0, delete the head
        return; // exit
    }

    node_t* previous = NULL; // variable to keep track of previous node
    node_t* current = list->head; // variable to keep track of current node

    for (int curr = 0; curr < position && current != NULL; curr++) { // traverse to position whilst keeping track of previous node aswell
        previous = current;
        current = current->next;
    }
    if (previous == NULL || NULL == current) return; // if previous node or current node is NULL, we cant delete anything

    previous->next = current->next; // remove the node from the list
    free(current); // free the node
    list->size--; // decrement the size of the list
}

/**
 * @brief Deletes the tail node of a list.
 * @param list the list to delete the tail of
 */
void DeleteTail(linkedlist_t* list) {
    DeleteNodeAtPosition(list, list->size-1);
}

/**
 * @brief Creates a linked list with a specified amount of initialised nodes.
 * @param size the amount of nodes to create
 * @return linkedlist_t*
 */
linkedlist_t* CreateList(const int size) {
    linkedlist_t* tmp = malloc( sizeof(linkedlist_t) ); // allocate memory for the list
    if (NULL == tmp) {
        printf("%s", ERR_ALLOC);
        return NULL;
    }
    for (int i = 0; i < size; i++) { // Create the desired amount of nodes inside the linked list
        InsertAtHead(tmp, CreateNode(i%(INT_MAX-1)));
    }

    return tmp; // return pointer to the list
}

/**
 * @brief Checks if a linked list is empty.
 * @param list the list to check
 * @return 1 if empty, 0 if not
 */
int IsEmpty(const linkedlist_t* list) {
    if (NULL == list || NULL == list->head) return 1;
    return 0;
}

/**
 * @brief Reverses a linked list
 * @param list list to reverse
 */
void ReverseList(linkedlist_t* list) {
    if (IsEmpty(list)) return;

    // Declare and initialise helper variables
    node_t* prev = NULL; // pointer to previous node
    node_t* next = NULL; // pointer to next node
    node_t* curr = list->head; // pointer to current node

    // reverse list: Iterate through the list until we reach the end
    while (curr != NULL) {
        next = curr->next; // save reference to next node
        curr->next = prev; // Reverse the arrow
        prev = curr; // Make previous go forward by 1
        curr = next; // Make current go forward by 1
    }
    // Mark the last node as the new head
    list->head = prev;
}