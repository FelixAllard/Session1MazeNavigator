//
// Created by xilef on 9/25/2025.
//

#ifndef MAZEPROJECTSHERBROOKES1_NODELIST_H
#define MAZEPROJECTSHERBROOKES1_NODELIST_H

// Coordinate struct
typedef struct {
    int x;
    int y;
} Coordinate;

// Node struct
typedef struct Node {
    Coordinate coord;
    struct Node* next;
} Node;

void append(Node** head, int x, int y);
void printList(Node* head);
void freeList(Node* head);

#endif //MAZEPROJECTSHERBROOKES1_NODELIST_H