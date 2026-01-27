/**
* 
* @defgroup module FILE_DISC_SPACE_H file_disc_space
*
* @brief Headerfile file_disc_space.h
*
* This module contains function declarations for file_disc_space.c
* The functions declared in this module is a function that calculates disc space for a file
* and calculates disc space for a directory.
* 
*
* @author Viktor Vikström, ens22vvm, vivi0427@student.umu.se
* @since 2024-10-21.
*
* @{
*/

#ifndef FILE_DISC_SPACE_H
#define FILE_DISC_SPACE_H

#include "queue.h"
#include "info.h"
#include "mdu.h"

/**
 * @brief Calculate disc space for a file.
 * 
 * Calculates disc space for a file.
 * If the file is a directory the function will call calulate_directory.
 * 
 * @param file_name The name of the file.
 * @param the_info The info struct.
 * 
 * @return The size of the file.
 */
long int calculate_disc_space(char *file_name, struct info *the_info);

/**
 * @brief Calulate disc space for a directory.
 * 
 * Calculate all files inside a directory.
 * If a sub-directory is found the sub-directory will be placed in the queue.
 * The queue is inside struct info.
 * 
 * @param directory_name The name of the directory.
 * @param the_info The info struct.
 * 
 * @return The size of all files in the directory.
 */
long int calculate_directory(char *directory_name, struct info *the_info);

#endif /*FILE_DISC_SPACE_H*/