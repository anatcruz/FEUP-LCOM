#ifndef KEYBOARD
#define KEYBOARD

#include <lcom/lcf.h>

/** @defgroup keyboard keyboard
 * @{
 *
 * @brief Keyboard-related interrupt functions
 */

#define KEYBOARD_IRQ 1
#define KEYBOARD_HOOK_ID 1
#define KEYBOARD_MASK BIT(KEYBOARD_HOOK_ID)

#define KEYBOARD_TWO_BYTES_MSB 0xE0

/**
 * @brief Struct that represents a keyboard packet
 */
typedef struct keyboard_packet {
  uint8_t bytes[2]; /**< @brief The raw bytes of the keyboard packet */
  uint8_t n_bytes; /**< @brief The number of bytes in the packet */
} keyboard_packet;

/**
 * @brief The second part of keyboard interrupt handling
 * 
 * Calls to this function should be preceded immediately by kbc_ih(void)
 * 
 * @param new_packet A keyboard_packet pointer that will get overwritten if the packet was fully parsed
 * @return true if the packet was overwritten with a new packet, otherwise false
 */
bool keyboard_ih2(keyboard_packet *new_packet);

/**
 * @brief Subscribes to keyboard interrupts
 * @return 0 if successful, otherwise it was not successful
 */
int keyboard_ih_subscribe();

/**
 * @brief Unsubscribes to keyboard interrupts
 * @return 0 if successful, otherwise it was not successful
 */
int keyboard_ih_unsubscribe();

/**
 * @brief Enables keyboard interrupts
 * @return 0 if successful, otherwise it was not successful
 */
int keyboard_ih_enable();

/**
 * @brief Disables keyboard interrupts
 * @return 0 if successful, otherwise it was not successful
 */
int keyboard_ih_disable();

/** @} end of keyboard */

#endif
