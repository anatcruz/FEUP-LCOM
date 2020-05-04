#ifndef KBC
#define KBC

#include <lcom/lcf.h>

#include "utils.h"

/** @defgroup kbc kbc
 * @{
 *
 * @brief Functions related to the keyboard and mouse controller.
 * 
 */

#define KBC_TICK_DELAY 20000

#define KBC_PARITY  BIT(7)
#define KBC_TIMEOUT BIT(6)
#define KBC_AUX     BIT(5)
#define KBC_INH     BIT(4)
#define KBC_A2      BIT(3)
#define KBC_SYS     BIT(2)
#define KBC_IBF     BIT(1)
#define KBC_OBF     BIT(0)

#define KBC_STAT_REG 0x64
#define KBC_COM_REG  0x64

#define KBC_OUT_BUF     0x60
#define KBC_COM_ARG_REG 0x60

#define KBC_READ_COM              0x20
#define KBC_WRITE_COM             0x60
#define KBC_SELF_TEST             0xAA
#define KBC_CHECK_KB_INTERFACE    0xAB
#define KBC_DISABLE_KBD_INTERFACE 0xAD
#define KBC_ENABLE_KBD_INTERFACE  0xAE
#define KBC_DISABLE_MOUSE         0xA7
#define KBC_ENABLE_MOUSE          0xA8
#define KBC_CHECK_MOUSE_INTERFACE 0xA9
#define KBC_WRITE_BYTE_TO_MOUSE   0XD4

#define KBC_COM_BYTE_DIS2 BIT(5)
#define KBC_COM_BYTE_DIS  BIT(4)
#define KBC_COM_BYTE_INT2 BIT(1)
#define KBC_COM_BYTE_INT  BIT(0)

/**
 * @brief Blocks the program by delay microseconds
 * @param delay The number of microseconds the program will be delayed
 */
void kbc_delay(int delay);

/**
 * @brief Sends a command to the kbc
 * @param command The command byte to be sent
 * @return 0 if successful, something else otherwise
 */
int kbc_write_command(uint8_t command);

/**
 * @brief Sends an argument to the kbc
 * @param arg The argument byte to be sent
 * @return 0 if successful, something else otherwise
 */
int kbc_write_command_arg(uint8_t arg);

/**
 * @brief Reads a command result from the kbc
 * @param result A pointer to the byte which will be rewritten
 * @return 0 if successful, something else otherwise
 */
int kbc_read_command_result(uint8_t *result);

/**
 * @brief Reads the command byte from the kbc
 * @param command_byte A pointer to the byte which will be rewritten
 * @return 0 if successful, something else otherwise
 */
int kbc_read_command_byte(uint8_t *command_byte);

/**
 * @brief Sends a command byte to the kbc
 * @param command_byte The command byte to be sent
 * @return 0 if successful, something else otherwise
 */
int kbc_write_command_byte(uint8_t command_byte);

/**
 * @brief Reads the status of the kbc
 * @param status A pointer to the byte which will be rewritten
 * @return 0 if successful, something else otherwise
 */
int kbc_read_status(uint8_t *status);

/** @} end of kbc */

#endif
