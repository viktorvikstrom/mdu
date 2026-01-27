/*
 
Systemnära programmering
Ou3*
File:         mdu.c
Description:   

This source file creates and uses threads to calculate the amount of disc space a list of files occupy.
Each file given as input will be calculated separately and printed out to stdout.
The flag "-j" can be used to set the amount of threads the program should use.
If flag "-j" is not used the program will run with one thread.

Input is: ./mdu optional: -j (amount of threads to be used.) Files separated with space.

Author:       Viktor Vikström
CS username:  ens22vvm
Date:         2024-10-21

*/

#include "mdu.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <getopt.h>
#include <pthread.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {

    // The amount of threads.
    long int number_of_threads = 1;

    // The exit status.
    bool exit_status = false;
    struct info *the_info;
    int opt;

    while ((opt = getopt(argc, argv, "j:")) != -1) {
        switch(opt) {
            case 'j':
                number_of_threads = strtol(optarg, NULL, 10);
                break;
            default:
                fprintf(stderr, "Usage: %s [-j num_threads] [file ...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    for (int i = optind; i < argc; i++) {

        // Creates a info struct with input file.
        the_info = create_info(argv[i]);

        // Creates "number_of_threads" amount of threads.
        pthread_t *the_threads = create_threads(number_of_threads, the_info);

        // Joins all threads. 
        join_threads(number_of_threads, the_threads);

        // Prints the result.
        printf("%ld\t%s\n", the_info->amount_of_disc_space, argv[i]);

        // Transfers the exit status.
        exit_status = the_info->exit_code;
        
        // Deallocates the info and destroys condition variable and mutex.
        cleanup_info_and_sync(the_info);
    }

    if (exit_status) {

        exit(EXIT_FAILURE);

    } 

    exit(EXIT_SUCCESS);

}

void cleanup_info_and_sync(struct info *the_info) {

    pthread_mutex_destroy(the_info->add_to_space_mutex);
    pthread_mutex_destroy(the_info->the_queue_mutex);
    pthread_cond_destroy(the_info->queue_cond);
    destroy_info(the_info);
}