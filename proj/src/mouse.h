#ifndef MOUSE
#define MOUSE

#include <stdint.h>
#include <stdbool.h>

/** @defgroup mouse mouse
 * @{
 *
 * @brief Mouse-related interrupt and command-sending functions
 */

#define MOUSE_IRQ 12
#define MOUSE_HOOK_ID 2
#define MOUSE_MASK BIT(MOUSE_HOOK_ID)

#define MOUSE_BYTE_1_Y_OVFL       BIT(7)
#define MOUSE_BYTE_1_X_OVFL       BIT(6)
#define MOUSE_BYTE_1_MSB_Y_DELTA  BIT(5)
#define MOUSE_BYTE_1_MSB_X_DELTA  BIT(4)
#define MOUSE_BYTE_1_BIT_SET_TO_1 BIT(3)
#define MOUSE_BYTE_1_MB           BIT(2)
#define MOUSE_BYTE_1_RB           BIT(1)
#define MOUSE_BYTE_1_LB           BIT(0)

#define MOUSE_COM_RESET                  0xFF
#define MOUSE_COM_RESEND                 0xFE
#define MOUSE_COM_SET_DEFAULTS           0xF6
#define MOUSE_COM_DISABLE_DATA_REPORTING 0xF5
#define MOUSE_COM_ENABLE_DATA_REPORTING  0xF4
#define MOUSE_COM_SET_SAMPLE_RATE        0xF3
#define MOUSE_COM_SET_REMOTE_MODE        0xF0
#define MOUSE_COM_READ_DATA              0xEB
#define MOUSE_COM_SET_STREAM_MODE        0xEA
#define MOUSE_COM_STATUS_REQUEST         0xE9
#define MOUSE_COM_SET_RESOLUTION         0xE8
#define MOUSE_COM_SET_SCALING_2_1        0xE7
#define MOUSE_COM_SET_SCALING_1_1        0xE6

#define MOUSE_RESPONSE_ACK   0xFA
#define MOUSE_RESPONSE_NACK  0xFE
#define MOUSE_RESPONSE_ERROR 0xFC

/**
 * @brief Struct that represents a mouse packet.
 * This struct was provided by one of LCOM's header files
 */
typedef struct mouse_packet {
  uint8_t bytes[3]; /**< @brief mouse packet raw bytes */
  bool rb; /**< @brief right mouse button pressed */
  bool mb; /**< @brief middle mouse button pressed */
  bool lb; /**< @brief left mouse button pressed */
  int16_t delta_x; /**< @brief mouse x-displacement: rightwards is positive */
  int16_t delta_y; /**< @brief mouse y-displacement: upwards is positive */
  bool x_ov; /**< @brief x-displacement overflow */
  bool y_ov; /**< @brief y-displacement overflow */
} mouse_packet;

/**
 * @brief The first part of mouse interrupt handling
 * 
 * Calls to this function should be succeeded immediately by mouse_parse_packet(mouse_packet *packet)
 */
void (mouse_ih)(void);

/**
 * @brief Sends a command to the mouse
 * @param command The command byte to be sent
 * @return 0 if successful, something else otherwise
 */
int mouse_send_command(uint8_t command);

/**
 * @brief The second part of mouse interrupt handling
 * 
 * Calls to this function should be preceded immediately by mouse_ih(void)
 * 
 * @param packet A mouse_packet pointer that will get overwritten if the packet was fully parsed
 * @return true if the packet was overwritten with a new packet, otherwise false
 */
bool mouse_parse_packet(mouse_packet *packet);

/**
 * @brief Subscribes to mouse interrupts
 * @return 0 if successful, otherwise it was not successful
 */
int mouse_ih_subscribe();

/**
 * @brief Unsubscribes to mouse interrupts
 * @return 0 if successful, otherwise it was not successful
 */
int mouse_ih_unsubscribe();

/**
 * @brief Enables mouse interrupts
 * @return 0 if successful, otherwise it was not successful
 */
int mouse_ih_enable();

/**
 * @brief Disables mouse interrupts
 * @return 0 if successful, otherwise it was not successful
 */
int mouse_ih_disable();

/** @} end of mouse */

#endif
