/*
 
Systemnära programmering
Ou3*
File:         thread.c
Description:   

This source file contains function definitions for a queue.
The functions in this source files is:
Create_queue that dynamically allocate memory for the queue.
Create_node that dynamically allocate memory for a node in the queue.
Enqueue that adds a value to the queue using FIFO.
Dequeue.
Queue_is_empty that checks if the queue is empty.

Author:       Viktor Vikström
CS username:  ens22vvm
Date:         2024-10-21

*/

#include "queue.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Que *create_queue(void) {

    Que *the_queue = malloc(sizeof(Que));

    if (the_queue == NULL) {
        perror("Failed to malloc queue.\n");
        exit(EXIT_FAILURE);
    }

    the_queue->first = NULL;
    the_queue->rear = NULL;

    return the_queue;
}

Node *create_node(const char *file_name) {

    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Failed to malloc new_node");
        exit(EXIT_FAILURE);
    }

    new_node->file_name = malloc(strlen(file_name) + 1);
    if (new_node->file_name == NULL) {
        perror("Failed to malloc file_name");
        free(new_node);
        exit(EXIT_FAILURE);
    }

    strcpy(new_node->file_name, file_name);
    new_node->prev = NULL;
    
    return new_node;
}

void enqueue(const char *file_name, Que *the_queue) {
    Node *new_node = create_node(file_name);
    if (new_node == NULL) {
        perror("Failed to allocate memory in create_node");
        exit(EXIT_FAILURE);
    }

    if (the_queue->rear == NULL) {

        the_queue->rear = new_node;
        the_queue->first = new_node;

    } else {

        the_queue->rear->prev = new_node;
        the_queue->rear = new_node;
        
    }
}

char *dequeue(Que *the_queue) {

    Node *first_node = the_queue->first;
    if (first_node == NULL) {
        return NULL;
    }

    char *file_name = malloc(strlen(first_node->file_name) + 1);
    if (file_name == NULL) {
        perror("Failed to allocate memory for file_name in dequeue\n");
        exit(EXIT_FAILURE);
    }

    strcpy(file_name, first_node->file_name);

    the_queue->first = first_node->prev;
    if (the_queue->first == NULL) {
        the_queue->rear = NULL;
    }

    free(first_node->file_name);
    free(first_node);

    return file_name;
}

bool queue_is_empty(Que *the_queue) {
    return the_queue->first == NULL;
}