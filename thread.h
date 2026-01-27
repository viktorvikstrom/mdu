/**
* 
* @defgroup module THREAD_H thread
*
* @brief Headerfile thread.h
*
* This module contains function declarations for thread.c
* It contain functions that saftley syncronize threads, a thread function,
* create threads and a function that joins all created threads.
*
* @author Viktor Vikström, ens22vvm, vivi0427@student.umu.se
* @since 2024-10-21.
*
* @{
*/

#ifndef THREAD_H
#define THREAD_H

#include "info.h"
#include "file_disc_space.h"
#include <stdio.h>

/**
 * @brief The thread function.
 * 
 * A function for the threads so that they can calculate with eachother in
 * a effective way.
 * 
 * @param queue The queue with file-names.
 */
void *thread_traversal_function(void *inf);

/**
 * @brief Creates threads.
 * 
 * A function that creates a amount of threads with call to function pthread_create.
 * 
 * This function dynamically allocates memory for a array of threads.
 * 
 * @param amount The amount of threads to create.
 * @param the_info A info structure with information of the file etc.
 */
pthread_t *create_threads(int amount, struct info *the_info);

/**
 * @brief A function to join a amount of threads.
 * 
 * A function that join a amount of threads with call to function pthread_join.
 * 
 * @param amount The amount of threads created.
 * @param the_threads The array of threads.
 */
void join_threads(int amount, pthread_t *the_threads);

/**
 * @brief Adds a number to the result.
 * 
 * Saftley adds a number to the result using mutex.
 * 
 * @param the_info The info struct.
 * @param the_result The number to be added.
 * @param the_mutex The mutex used for adding to size.
 */
void add_to_amount_of_space(struct info *the_info, long int the_result, pthread_mutex_t *the_mutex);

/**
 * @brief Set exit code in info struct.
 * 
 * Saftley sets exit code in info struct using mutex.
 */
void set_exit_code_locked_mutex(struct info *the_info);

/**
 * @brief Enqueue path and signal.
 * 
 * Saftley enqueue path name using mutex.
 * Also sends one signal that directory is in queue.
 * 
 * @param path The path.
 * @param the_info The info struct.
 */
void enqueue_locked_mutex_and_signal(const char *path, struct info *the_info);

/**
 * @brief Locks a mutex.
 * @param mutex The mutex.
 */
void mutex_lock_with_error_handeling(pthread_mutex_t *mutex);

/**
 * @brief Unlocks a mutex.
 * @param mutex The mutex.
 */
void mutex_unlock_with_error_handeling(pthread_mutex_t *mutex);

/**
 * @brief Condition variable wait.
 * Calls function pthread_cond_wait with error handeling.
 */
void cond_wait_with_error_handeling(pthread_cond_t *cond, pthread_mutex_t *mutex);

/**
 * @brief Condition variable broadcast.
 * Calls function pthread_broadcast with error handeling.
 */
void cond_broadcast_with_error_handeling(pthread_cond_t *cond);

#endif /*THREAD_H*/