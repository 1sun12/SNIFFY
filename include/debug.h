
#ifndef DEBUG_H
#define DEBUG_H

/**
 * @brief Elite-C-Macro to output error message and then close the program
 */
#define exit_with_error(msg) do {perror(msg); return(EXIT_FAILURE);} while(0)

/**
 * @brief Error check that checks existance of incoming `self` first
 */
#define does_exist(obj) do {if(obj == NULL){perror("\n[ERROR]:does_exist"); return;}} while(0)

/**
 * @brief If 1, output additional debug messages (change to 0, remove extra messages)
 */
#define OUTPUT_DEBUG 1

/**
 * @brief Output a basic informational debug message
 */
#define OUTPUT_D_MSG(msg) do {if(OUTPUT_DEBUG) {printf("\n[INFO]:%s\n", msg);}} while(0)

#endif