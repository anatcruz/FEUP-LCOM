#ifndef TIMER
#define TIMER 

#include <lcom/lcf.h>

/** @defgroup timer timer
 * @{
 *
 * @brief Timer interrupt-related functions
 */

#define TIMER_INTERRUPT_FREQ 60
#define TIMER_IRQ 0
#define TIMER_HOOK_ID 0
#define TIMER_MASK BIT(TIMER_HOOK_ID)

/**
 * @return The number of interrupts the timer has triggered
 */
int timer_get_counter();

/**
 * @brief Subscribes to timer interrupts
 * @return 0 if successful, otherwise it was not successful
 */
int timer_ih_subscribe();

/**
 * @brief Unsubscribes to timer interrupts
 * @return 0 if successful, otherwise it was not successful
 */
int timer_ih_unsubscribe();

/**
 * @brief Enables timer interrupts
 * @return 0 if successful, otherwise it was not successful
 */
int timer_ih_enable();

/**
 * @brief Disables timer interrupts
 * @return 0 if successful, otherwise it was not successful
 */
int timer_ih_disable();

/** @} end of timer */

#endif

