/**
* 
* @defgroup module MDU_H mdu
*
* @brief Headerfile mdu.h
*
* This module contains one function declaration for mdu.c
*
* The function declarated in this module is a help function to destroy a info struct
* And destroy mutex and condition variables used in the source file.
* 
*
* @author Viktor Vikström, ens22vvm, vivi0427@student.umu.se
* @since 2024-10-21.
*
* @{
*/

#ifndef MDU_H
#define MDU_H

#include "queue.h"
#include "file_disc_space.h"
#include "info.h"
#include "thread.h"

/**
 * @brief Cleans up memory and sync-tools
 * 
 * Deallocate the info struct and destroys the sync-tools.
 * 
 */
void cleanup_info_and_sync(struct info *the_info);

#endif /*MDU_H*/