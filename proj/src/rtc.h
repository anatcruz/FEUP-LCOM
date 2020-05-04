#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <lcom/utils.h>

/** @defgroup rtc rtc
 * @{
 *
 * @brief RTC-related interrupt and register-reading/writing functions
 */

#define RTC_IRQ 8
#define RTC_HOOK_ID 3
#define RTC_MASK BIT(RTC_HOOK_ID)

#define RTC_SECONDS          0
#define RTC_SECONDS_ALARM    1
#define RTC_MINUTES          2
#define RTC_MINUTES_ALARM    3
#define RTC_HOURS            4
#define RTC_HOURS_ALARM      5
#define RTC_DAY_OF_THE_WEEK  6
#define RTC_DAY_OF_THE_MONTH 7
#define RTC_MONTH            8
#define RTC_YEAR             9
#define RTC_REGISTER_A       10
#define RTC_REGISTER_B       11
#define RTC_REGISTER_C       12
#define RTC_REGISTER_D       13

#define RTC_ADDR_REG         0x70
#define RTC_DATA_REG         0x71

#define RTC_REG_A_UIP        BIT(7)

#define RTC_REG_B_SET        BIT(7)
#define RTC_REG_B_PIE        BIT(6)
#define RTC_REG_B_AIE        BIT(5)
#define RTC_REG_B_UIE        BIT(4)
#define RTC_REG_B_SQWE       BIT(3)
#define RTC_REG_B_DM         BIT(2)
#define RTC_REG_B_24_12      BIT(1)
#define RTC_REG_B_DSE        BIT(0)

#define RTC_REG_C_IRQF       BIT(7)
#define RTC_REG_C_PF         BIT(6)
#define RTC_REG_C_AF         BIT(5)
#define RTC_REG_C_UF         BIT(4)

/**
 * @brief Handles RTC interrupts
 * 
 * @return True if it was an alarm interrupt, otherwise false
 */
bool rtc_ih();

/**
 * @brief Subscribes to RTC interrupts
 * @return 0 if successful, otherwise it was not successful
 */
int rtc_ih_subscribe();

/**
 * @brief Unsubscribes to RTC interrupts
 * @return 0 if successful, otherwise it was not successful
 */
int rtc_ih_unsubscribe();

/**
 * @brief Enables RTC interrupts
 * @return 0 if successful, otherwise it was not successful
 */
int rtc_ih_enable();

/**
 * @brief Disables RTC interrupts
 * @return 0 if successful, otherwise it was not successful
 */
int rtc_ih_disable();

/**
 * @brief Writes the RTC register at position reg 
 * 
 * @param reg The register to be written
 * @param data The byte that is going to be written in the register
 */
void    rtc_write_reg(uint8_t reg, uint8_t data);

/**
 * @brief Reads the RTC register at position reg
 * 
 * @param reg The register to be read
 * @return The byte of the register at position reg
 */
uint8_t rtc_read_reg(uint8_t reg);

/**
 * @return The hour (Only valid if RTC inturrupts are subscribed to)
 */
uint8_t rtc_get_hour  ();

/**
 * @return The minute (Only valid if RTC inturrupts are subscribed to)
 */
uint8_t rtc_get_minute();

/**
 * @return The second (Only valid if RTC inturrupts are subscribed to)
 */
uint8_t rtc_get_second();


/** @} end of rtc */
