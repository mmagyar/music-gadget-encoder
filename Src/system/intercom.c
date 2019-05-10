#include "intercom.h"
#include "../util/dataframe.h"
#include "uart.h"
#include "stm32g070xx.h"
#include "../util/safe_array.h"

#define SERIALIZE(STRUCT_NAME) \
    Mcu_uid uid = get_uid(); \
    u8* uid_byte = (u8*)&uid; \
    u8  send[ICOM_LARGEST_STRUCT +12 +1]; \
    loop(x, 12) {send[x] = uid_byte[x]; } \
    send[12] =  MT_ ## STRUCT_NAME; \
    u8 struct_size = message_size[MT_ ## STRUCT_NAME]; \
    loop(x, struct_size) { \
        send[x + 12 + 1] = ((u8* ) input)[x];  \
    }\
    send_intercom(send, struct_size + 1 + (sizeof(Mcu_uid)));

#define DESERIALIZE(STRUCT_NAME) \
        ((u8*)&receive_buffer->buffer.STRUCT_NAME)[byte_counter] = buffer[i]; \
                if (byte_counter >= message_size[receive_buffer->type]) { \
                    icom_receive_ ## STRUCT_NAME(receive_buffer->buffer.STRUCT_NAME); \
                } \

#define DESERIALIZE_CASE(STRUCT_NAME) \
    case MT_ ## STRUCT_NAME : \
        DESERIALIZE(STRUCT_NAME) \
    break; \

u8 message_size[8] = {
        0, sizeof(Control_change), sizeof(Button_press), sizeof(Led_update)
};

void send_uart(u8 data) {
    send_data_uart_4(data);
}

void send_intercom(u8 * data, u16 length) {

    send_on_the_fly(data, length, &send_uart);

}

Mcu_uid get_uid() {
    u32 * uid_location = (u32*) UID_BASE;
    Mcu_uid uid = {
            uid_location[0],
            uid_location[1],
            uid_location[2] };

    return uid;
}

void icom_send_control_change(Control_change * input) {
    SERIALIZE(control_change)
}

void icom_send_button_press(Button_press * input) {
    SERIALIZE(button_press)
}

void icom_send_led_update(Led_update * input) {
    SERIALIZE(led_update);
}

/**
 * This will read structs, there can be may structs following each other
 */
void icom_read_message(u8 * buffer, u16 size, Icom_send * receive_buffer) {
    bool in_process = false;
    Message_type processing = MT_ping;
    u8 bytes_remaining = 0;
    u8 byte_counter = 0;
    u8 sender_id_bytes_left = sizeof(Mcu_uid);
    loop(i, size)
    {
        if(!sender_id_bytes_left){
            ((u8 *)&receive_buffer->uid)[i] = buffer[i];
            sender_id_bytes_left--;
        } else if (!in_process) { //Start of a new struct
            receive_buffer->type = buffer[i];
            if (processing >= 8) {
                //ERROR, bad struct id
                return;
            }
            bytes_remaining = message_size[processing];
            if (processing != MT_ping) in_process = true;
            byte_counter = 0;
        } else {
            bytes_remaining--;
            byte_counter++;
            switch (processing) {
                DESERIALIZE_CASE(control_change)
                DESERIALIZE_CASE(button_press)
                DESERIALIZE_CASE(led_update)
            default:
                //ERROR _ UNKNOWN DATA
                return;
            }
            if (!bytes_remaining) {
                in_process = false;
            }
        }
    }
}

