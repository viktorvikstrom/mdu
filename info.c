/*
 
Systemnära programmering
Ou3*
File:         thread.c
Description:   

This source file contains function definitions for a specific struct info.
It has functions that allocate memory and create the struct, destroys the struct,
initialize the mutexs and condition variables.

Author:       Viktor Vikström
CS username:  ens22vvm
Date:         2024-10-21

*/

#include "info.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

struct info *create_info(char *the_file) {

    struct info *the_info = malloc(sizeof(struct info));
    if (the_info == NULL) {
        perror("Failed to allocate memory for the_info\n");
        exit(EXIT_FAILURE);
    }

    alloc_info_members(the_info);
    enqueue(the_file, the_info->the_queue);
    init_mutex_and_cond(the_info);

    the_info->amount_of_disc_space = 0;
    the_info->active_threads = 0;
    the_info->exit_code = false;

    return the_info;
}

void destroy_info(struct info *the_info) {

    free(the_info->queue_cond);
    free(the_info->the_queue_mutex);
    free(the_info->add_to_space_mutex);
    free(the_info->exit_failure_mutex);
    free(the_info->the_queue);
    free(the_info);

}

void init_mutex_and_cond(struct info *the_info) {

    // pthread_mutex_init(the_info->the_queue_mutex, NULL);
    // pthread_mutex_init(the_info->add_to_space_mutex, NULL);
    // pthread_mutex_init(the_info->exit_failure_mutex, NULL);
    init_mutex(the_info->the_queue_mutex);
    init_mutex(the_info->add_to_space_mutex);
    init_mutex(the_info->exit_failure_mutex);

    if (pthread_cond_init(the_info->queue_cond, NULL) != 0) {
        
        perror("Failed to init condition variable\n");
        exit(EXIT_FAILURE);

    }

}

void alloc_info_members(struct info *the_info) {

    the_info->the_queue = create_queue();
    if (the_info->the_queue == NULL) {
        free(the_info);
        perror("Failed to allocate memory for the_info->the_queue\n");
        exit(EXIT_FAILURE);
    }

    the_info->queue_cond = malloc(sizeof(pthread_cond_t));
    if (the_info->queue_cond == NULL) {
        free(the_info);
        perror("Failed to allocate memory for the_info->queue_cond\n");
        exit(EXIT_FAILURE);
    }

    the_info->the_queue_mutex = malloc(sizeof(pthread_mutex_t));
    if (the_info->the_queue_mutex == NULL) {
        free(the_info);
        perror("Failed to allocate memory for the_info->the_queue_mutex\n");
        exit(EXIT_FAILURE);
    }

    the_info->add_to_space_mutex = malloc(sizeof(pthread_mutex_t));
    if (the_info->add_to_space_mutex == NULL) {
        free(the_info);
        perror("Failed to allocate memory for the_info->add_to_space_mutex\n");
        exit(EXIT_FAILURE);
    }

    the_info->exit_failure_mutex = malloc(sizeof(pthread_mutex_t));
    if (the_info->exit_failure_mutex == NULL) {
        free(the_info);
        perror("Failed to alllocate memory for the_infor->exit_failure_mutex\n");
        exit(EXIT_FAILURE);
    }

}

void init_mutex(pthread_mutex_t *mutex) {

    if (pthread_mutex_init(mutex, NULL) != 0) {

        perror("Failed to init mutex\n");
        exit(EXIT_FAILURE);

    }
}