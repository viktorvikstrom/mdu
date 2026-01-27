/**
* Included libraries: stdlib.h, unistd.h and pthread.h
* 
* @defgroup module INFO_H info
*
* @brief Headerfile info.h
*
* This module contains function declarations for info.c
* 
* The header file contains a struct named info.
* Info contains several memebers such as three mutex, a condition variable,
* a queue and some other simple variables.
*
* The functions declared in this module is function that creates a info struct,
* initialize its condition variable and mutexes and a function that destroys a struct info.
* 
*
* @author Viktor Vikström, ens22vvm, vivi0427@student.umu.se
* @since 2024-10-21.
*
* @{
*/

#ifndef INFO_H
#define INFO_H

#include "queue.h"

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct info {

    Que *the_queue; /** < A pointer to the queue. */
    pthread_mutex_t *the_queue_mutex; /** < A pointer to the mutex used with the queue. */
    pthread_mutex_t *add_to_space_mutex; /** < A pointer to the mutex used with adding to amount_of_disc_space. */
    pthread_mutex_t *exit_failure_mutex; /** < A pointer to the mutex used when exit code is changed. */
    pthread_cond_t *queue_cond; /** < A pointer to the condition variable. */
    long int amount_of_disc_space; /** < The amount of disc space. */
    int active_threads; /** < A counter to the amount of active threads at the moment. */
    bool exit_code; /** < A variable that saves the exit code. */

};

/**
 * @brief Destroys a info struct.
 */
void destroy_info(struct info *the_info);

/**
 * @brief Creates a info struct.
 * 
 * This function dynamically allocates memory for a info struct.
 * 
 * The dynamically allocated memory can be destroyed with call to function: destroy_info.
 * 
 * @param the_file The file to get the size of.
 */
struct info *create_info(char *the_file);

/**
 * @brief Call init to all sync-functions.
 * 
 * Calls init for the condition variable and the mutex.
 * 
 * @param the_info The info struct.
 */
void init_mutex_and_cond(struct info *the_info);

/**
 * @brief Allocates members in struct.
 * 
 * Help function that dynamically allocates memory for a struct info members.
 * 
 * @param the_info The info struct.
 */
void alloc_info_members(struct info *the_info);

void init_mutex(pthread_mutex_t *mutex);

#endif /*INFO_H*/