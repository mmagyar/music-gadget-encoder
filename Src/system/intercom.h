#ifndef SYSTEM_INTERCOM_H_
#define SYSTEM_INTERCOM_H_
#include "../util/types.h"
#include "../util/error_log.h"
/**
 * Intercom between modules
 * Each message starts with the UID of the sending MCU - 12 bytes
 * Followed by the message count of that MCU - 4 bytes
 * This way we can avoid processing a message multiple time in any connection configuration
 * This header is followed by one or more messages
 * Each message should start with a Message type byte
 * followed the exact number of bytes that is assigned to that `Message_type`
 * in `message_size` array
 *
 */

#define ICOM_LARGEST_STRUCT 16

#define MAX_PEERS 16
typedef struct Mcu_uid {
    u32 wafer_coordinate;
    u32 lot_number;
    u32 wafer_number;
    u32 message_count;
} Mcu_uid;

typedef enum {
    MT_ping = 0,
    MT_control_change = 1,
    MT_button_press = 2,
    MT_led_update = 3
} Message_type;

/**
 * Size of the messages, the index is the Message_type enum
 */
u8 message_size[8];

typedef struct {
    u8 controller_num;
    u8 value;
//   u8 abc;
} Control_change;

typedef struct {
    u8 button_num;
} Button_press;

typedef struct {
    u16 led_number;
    u8 intensity;

} Led_update;

/**
 * Using the union means that we don't need to reserve memory for all the different
 * Possible structures, we just need one buffer, and it just consumes as much memory
 * as the largest structure
 */
typedef union {
    Control_change control_change;
    Button_press button_press;
    Led_update led_update;
} Icom_serialization_buffer;

u32 message_count;
typedef struct {
    Mcu_uid uid;
    u8 type;
    Icom_serialization_buffer buffer;
} Icom_send;

Mcu_uid peers[MAX_PEERS];

/**
 * This will read structs, there can be may structs following each other
 */
void icom_read_message(u8 * buffer, u16 size, Icom_send * receive_buffer);

void icom_send_control_change();
void icom_send_button_press(Button_press * input);

void (*icom_receive_control_change)(Control_change ch);
void (*icom_receive_button_press)(Button_press bp);
void (*icom_receive_led_update)(Led_update lu);
#endif /* SYSTEM_INTERCOM_H_ */
