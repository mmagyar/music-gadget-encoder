#include "intercom.h"
#include "../util/dataframe.h"
#include "uart.h"
#include "stm32g070xx.h"
#include "../util/safe_array.h"

u8 message_size[8] = {
        0, 2, 1, 3
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

void icom_send_control_change(Control_change * change) {
    u8 msg[16] = { };
    u8 i = 0;
    msg[i++] = MT_CONTROL_CHANGE;
    msg[i++] = change->controller_num;
    msg[i++] = change->value;
    send_intercom(msg, 3);
}

void icom_send_button_press(u8 button_num) {
    u8 msg[16] = { };
    u8 i = 0;
    //Maybe send the device id?
    msg[i++] = MT_CONTROL_CHANGE;
    msg[i++] = button_num;
    send_intercom(msg, 2);
}

/**
 * This will read structs, there can be may structs following each other
 */
void icom_read_message(u8 * buffer, u16 size, Icom_receive_buffer receive_buffer) {
    bool in_process = false;
    Message_type processing = MT_PING;
    u8 bytes_remaining = 0;
    u8 byte_counter = 0;
    loop(i, size)
    {
        //Start of a new struct
        if (!in_process) {
            processing = buffer[i];
            if (processing >= 8) {
                //ERROR, bad struct id
                return;
            }
            bytes_remaining = message_size[processing];
            if (processing != MT_PING) in_process = true;
            byte_counter = 0;
        } else {
            bytes_remaining--;
            byte_counter++;
            switch (processing) {
            case MT_CONTROL_CHANGE:
                switch (byte_counter) {
                case 0:
                    receive_buffer->ch.controller_num = buffer[i];
                    break;
                case 1:
                    receive_buffer->ch.value = buffer[i];
                    icom_receive_control_change(receive_buffer->ch);
                    break;
                default:
                    //ERROR
                }
                break;
            case MT_BUTTON_PRESS:
                receive_buffer->bp.button_num = buffer[i];
                icom_receive_button_press(receive_buffer->bp);
                break;
            case MT_LED_UPDATE:
                break;
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

