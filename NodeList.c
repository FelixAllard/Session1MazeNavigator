//
// Created by xilef on 9/25/2025.
//

#include "NodeList.h"

#include <stdio.h>
#include <stdlib.h>

///
///@def Simple Coordinate structure
typedef struct {
    int x;
    int y;
} Coordinate;

///
/*
///@struct Node
///@brief This is a simple Structure. It holds the coordinate and the next node. This way they can form a chain and create a List.
///@
///@author {Felix}
///@date {9/25/2025}
typedef struct Node {
    Coordinate coord;
    struct Node* next;
} Node;
*/

/// @brief This function adds a new Coordinate to the coordinate List. The coordinate will be at the end of the List.
/// @param x X Coordinate of the coordinate to add to the List
/// @param y Y Coordinate of the coordinate to add to the List
/// @return The created Node
Node* createNode(int x, int y) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->coord.x = x;
    newNode->coord.y = y;
    newNode->next = NULL;
    return newNode;
}

///
/// @param head
/// @param x
/// @param y
void append(Node** head, int x, int y) {
    Node* newNode = createNode(x, y);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to print the list
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("(%d, %d) -> ", temp->coord.x, temp->coord.y);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to free the list
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
