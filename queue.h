/**
* Included libraries: stdbool.h
* 
* @defgroup module QUEUE_H queue
*
* @brief Headerfile queue.h
*
* This module contains function declarations and two struct for queue.c
* 
* Struct node represents a node in the queue
* and Que represents the queue.
*
* The functions declarated in this module is functions for the queue.
* Create_queue creates a queue
* Create_node creates a node for the queue.
* Enqueue adds a value to the queue.
* Dequeue removes the first node and value from the queue.
* Queue_is_empty checks if the queue is empty.
* 
*
* @author Viktor Vikström, ens22vvm, vivi0427@student.umu.se
* @since 2024-10-21.
*
* @{
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct node {

    struct node *prev; /** < A pointer to the previous node in the queue. */
    char *file_name; /** < A pointer to the file path. */
    
} Node;

typedef struct queue {

    Node *first; /** < A pointer to the first node in the queue. */
    Node *rear; /** < A pointer to the last node in the queue. */

} Que;

/**
 * @brief Create a queue.
 * 
 * Dynamically allcoates memory for a queue.
 * 
 * The dynamically allocate memory created by this function can be destroyed by a call to free
 * if the queue is empty. Else dequeue until empty and then call free.
 * 
 * @return A queue.
 */
Que *create_queue(void);

/**
 * @brief Creates a node.
 * 
 * A function that creates a node for the queue.
 * 
 * @param file_name The file name.
 * @return A node.
 */
Node *create_node(const char *file_name);

/**
 * @brief Add a node to the queue.
 * 
 * Add a node last in the queue.
 * 
 * @param file_name The file name.
 * @param the_queue The queue.
 */
void enqueue(const char *file_name, Que *the_queue);

/**
 * @brief Removes the first node in the queue.
 * 
 * Removes the first node of the queue.
 * 
 * @param the_queue The queue.
 * 
 * @return The file name in the node.  
 */
char *dequeue(Que *the_queue);

/**
 * @brief Checks if queue is empty.
 * @return Boolean value.
 */
bool queue_is_empty(Que *the_queue);

#endif /*QUEUE_H*/