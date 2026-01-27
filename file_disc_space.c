/*
 
Systemnära programmering
Ou3*
File:         file_disc_space.c
Description:   

This source file contains function definitions to calculate the disc space of a file.

Author:       Viktor Vikström
CS username:  ens22vvm
Date:         2024-10-21

*/

#include "file_disc_space.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

long int calculate_disc_space(char *file_name, struct info *the_info) {

    struct stat file_stat;
    long int result = 0;

    if (lstat(file_name, &file_stat) == -1) {

        fprintf(stderr, "Failed to lstat file %s\n", file_name);
        set_exit_code_locked_mutex(the_info);

    }

    result += file_stat.st_blocks;

    if (S_ISDIR(file_stat.st_mode)) {

        result += calculate_directory(file_name, the_info);

    } 

    return result;
}

long int calculate_directory(char *directory_name, struct info *the_info) {

    struct dirent *entry;
    struct stat file_stat;
    long int result = 0;
    
    DIR *directory = opendir(directory_name);

    if (directory == NULL) {

        fprintf(stderr, "du: cannot read directory %s: Permission denied\n", directory_name);
        set_exit_code_locked_mutex(the_info);
        return 0;

    }

    char path[4096];
    
    while ((entry = readdir(directory)) != NULL) {

        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {

            int snprintf_return = snprintf(path, sizeof(path), "%s/%s", directory_name, entry->d_name);

            if (snprintf_return < 0) {

                perror("Failed snprintf\n");
                set_exit_code_locked_mutex(the_info);
                continue;
            }

            if (lstat(path, &file_stat) == -1) {

                perror("Couldnt lstat file in directory");
                set_exit_code_locked_mutex(the_info);
                continue;

            }

            if (S_ISDIR(file_stat.st_mode)) {

                enqueue_locked_mutex_and_signal(path, the_info);

            } else {

                result += file_stat.st_blocks;

            }
        }
    }

    closedir(directory);

    return result;
}