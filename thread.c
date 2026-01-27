/*
 
Systemnära programmering
Ou3*
File:         thread.c
Description:   

This source code contains function definitions saftley syncronize threads, create thread, a thread function
and a function that joins all threads.

Author:       Viktor Vikström
CS username:  ens22vvm
Date:         2024-10-21

*/

#include "thread.h"

void *thread_traversal_function(void *inf) {

    struct info *the_info = (struct info *)inf;
    char *the_file_path;
    int long res = 0;

    while (1) {

        mutex_lock_with_error_handeling(the_info->the_queue_mutex);

        while (queue_is_empty(the_info->the_queue) && the_info->active_threads > 0) {

            cond_wait_with_error_handeling(the_info->queue_cond, the_info->the_queue_mutex);

        }

        if (queue_is_empty(the_info->the_queue) && the_info->active_threads == 0) {

            cond_broadcast_with_error_handeling(the_info->queue_cond);
            mutex_unlock_with_error_handeling(the_info->the_queue_mutex);

            break;

        }
    
        the_file_path = dequeue(the_info->the_queue);
        the_info->active_threads++;

        mutex_unlock_with_error_handeling(the_info->the_queue_mutex);

        res = calculate_disc_space(the_file_path, the_info);
        free(the_file_path);

        add_to_amount_of_space(the_info, res, the_info->add_to_space_mutex);

        mutex_lock_with_error_handeling(the_info->the_queue_mutex);
        the_info->active_threads--;

        if (the_info->active_threads == 0 && queue_is_empty(the_info->the_queue)) {

            cond_broadcast_with_error_handeling(the_info->queue_cond);

        }

        mutex_unlock_with_error_handeling(the_info->the_queue_mutex);

    }

    return NULL;
}

pthread_t *create_threads(int amount, struct info *the_info) {

    pthread_t *the_threads = malloc(sizeof(pthread_t) * amount);
    if (the_threads == NULL) {

        perror("Failed malloc in create threads\n");
        exit(EXIT_FAILURE);

    }

    for (int i = 0; i < amount; i++) {

        if (pthread_create(&the_threads[i], NULL, thread_traversal_function, the_info) != 0) {

            perror("Failed to create thread\n");
            exit(EXIT_FAILURE);

        }
    }

    return the_threads;
}

void join_threads(int amount, pthread_t *the_threads) {

    for (int i = 0; i < amount; i++) {

        if (pthread_join(the_threads[i], NULL) != 0) {

            perror("Failed to join threads.\n");
            exit(EXIT_FAILURE);

        }
    }

    free(the_threads);

}

void add_to_amount_of_space(struct info *the_info, long int the_result, pthread_mutex_t *the_mutex) {

    mutex_lock_with_error_handeling(the_mutex);

    the_info->amount_of_disc_space += the_result;

    mutex_unlock_with_error_handeling(the_mutex);

}

void set_exit_code_locked_mutex(struct info *the_info) {

    mutex_lock_with_error_handeling(the_info->exit_failure_mutex);

    the_info->exit_code = true;

    mutex_unlock_with_error_handeling(the_info->exit_failure_mutex);

}

void enqueue_locked_mutex_and_signal(const char *path, struct info *the_info) {

    mutex_lock_with_error_handeling(the_info->the_queue_mutex);

    enqueue(path, the_info->the_queue);

    if (pthread_cond_signal(the_info->queue_cond) != 0) {
        
        perror("Failed to signal condition variable\n");
        exit(EXIT_FAILURE);
    }

    mutex_unlock_with_error_handeling(the_info->the_queue_mutex);

}

void mutex_lock_with_error_handeling(pthread_mutex_t *mutex) {

    if (pthread_mutex_lock(mutex) != 0) {

        perror("Failed to lock mutex\n");
        exit(EXIT_FAILURE);
    }
}

void mutex_unlock_with_error_handeling(pthread_mutex_t *mutex) {

    if (pthread_mutex_unlock(mutex) != 0) {

        perror("Failed to unlock mutex\n");
        exit(EXIT_FAILURE);

    }
}

void cond_wait_with_error_handeling(pthread_cond_t *cond, pthread_mutex_t *mutex) {

    if (pthread_cond_wait(cond, mutex) != 0) {

        perror("Failed to wait cond\n");
        exit(EXIT_FAILURE);

    }
}

void cond_broadcast_with_error_handeling(pthread_cond_t *cond) {

    if (pthread_cond_broadcast(cond) != 0) {

        perror("Failed to broadcast condition variable\n");
        exit(EXIT_FAILURE);

    }
}