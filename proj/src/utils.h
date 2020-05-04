#ifndef UTILS
#define UTILS

#include <lcom/lcf.h>
#include <stdint.h>

// Already defined in lcom/utils.h
// #ifndef BIT
// #  define BIT(n) (1 << (n))
// #endif

#ifdef LAB3
int lab3_n_calls();
#endif

/** @defgroup utils utils
 * @{
 *
 * @brief Utility functions
 */

/** @brief Reads a byte from memory
 *  
 * @param port The memory address (normally in hexadecimal)
 * @param value A pointer to a byte, which will be rewritten with the value in memory
 * 
 * @return 0 if successful, otherwise it was not successful
 */
int util_sys_inb(int port, uint8_t *value);

/** @brief Converts a value from bcd format to decimal format
 *  
 * @param hex The value in bcd format
 * 
 * @return The value in decimal format
 */
uint8_t bcd_to_decimal(uint8_t hex);

/** @brief Converts a value from decimal format to bcd format
 *  
 * @param decimal The value in decimal format
 * 
 * @return The value in bcd format
 */
uint8_t decimal_to_bcd(uint8_t decimal);

/** @} end of utils */

#endif
