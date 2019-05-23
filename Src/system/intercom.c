#include "intercom.h"
#include "../util/dataframe.h"
#include "uart.h"
#include "stm32g070xx.h"
#include "../util/safe_array.h"

#define DO_FORWARD true
#define SERIALIZE_FORWARD(MCU_UID_PTR, STRUCT_NAME, STRUCT_VARIABLE, SKIP_PORT) \
    u8* uid_byte = (u8*)(MCU_UID_PTR); \
    u8  send[ICOM_LARGEST_STRUCT + 1 + (sizeof(Mcu_uid))]; \
    loop(x, (sizeof(Mcu_uid))) {send[x] = uid_byte[x]; } \
    send[(sizeof(Mcu_uid))] =  MT_ ## STRUCT_NAME; \
    u8 struct_size = message_size[MT_ ## STRUCT_NAME]; \
    loop(x, struct_size) { \
        send[x + 1 + (sizeof(Mcu_uid))] = ((u8* ) STRUCT_VARIABLE)[x];  \
    }\
    send_intercom(send, struct_size + 1 + (sizeof(Mcu_uid)), SKIP_PORT);

#define SERIALIZE(STRUCT_NAME) \
    Mcu_uid uid = get_uid_and_increment_counter(); \
    SERIALIZE_FORWARD(&uid, STRUCT_NAME, input,  0xFF);

#define DESERIALIZE(STRUCT_NAME) \
        ((u8*)&receive_buffer->buffer.STRUCT_NAME)[byte_counter++] = buffer[i]; \
                if (byte_counter >= message_size[receive_buffer->type]) { \
                    icom_receive_ ## STRUCT_NAME(peer, receive_buffer->buffer.STRUCT_NAME); \

#ifdef DO_FORWARD
#define FORWARD(STRUCT_NAME, SKIP_PORT) \
    SERIALIZE_FORWARD(peer, STRUCT_NAME, (&receive_buffer->buffer.STRUCT_NAME), SKIP_PORT );
#else
#define FORWARD(STRUCT_NAME)
#endif

#define DESERIALIZE_CASE(STRUCT_NAME) \
    case MT_ ## STRUCT_NAME : \
        DESERIALIZE(STRUCT_NAME) \
        FORWARD(STRUCT_NAME, source_port) \
                }\
    break;

Mcu_uid peers[MAX_PEERS] = { 0 };

u8 message_size[8] = {
        0, sizeof(Control_change), sizeof(Button_press), sizeof(Led_update)
};
/* This value is chosen, so that this will override any other current code, and will overflow  */
#define MESSAGE_COUNT_RESET 0xFFFFFFFF

u32 message_count = MESSAGE_COUNT_RESET;

u16 mcu_uid_get_index(Mcu_uid * input) {
    loop(x,MAX_PEERS)
    {
        Mcu_uid * id = &peers[x];
        if (id->wafer_number == input->wafer_number) {
            if (id->lot_number == input->lot_number) {
                if (id->wafer_coordinate == input->wafer_coordinate) {
                    return x;
                }

            }
        }
    }
    return 0xFFFF;
}

/**
 * Returns the index it inserted into
 */
u16 mcu_uid_insert_first_empty(Mcu_uid * input) {
    loop(x,MAX_PEERS)
    {
        Mcu_uid * id = &peers[x];
        if (!id->wafer_number) {
            if (!id->lot_number) {
                if (!id->wafer_coordinate) {
                    peers[x] = *input;
                    return x;
                }

            }
        }
    }
    log_error(EC_COMM_PEER_LIMIT_EXCEEDED, 'm');
    //ERROR when could not write
    return 0xFFFF;
}

/**
 * Returns true if the message should be processed
 */
bool mcu_uid_increment_count(u16 local_id, Mcu_uid * input) {
    bool found = false;

    Mcu_uid * id = &peers[local_id];
    if (id->wafer_number == input->wafer_number) {
        if (id->lot_number == input->lot_number) {
            if (id->wafer_coordinate == input->wafer_coordinate) {

                u32 current = peers[local_id].message_count;
                u32 new = input->message_count;

                //Next should be overflow
                if (current == MESSAGE_COUNT_RESET) {
                    if (new == MESSAGE_COUNT_RESET) {
                        //This means that it's the same message, we should ignore it
                        return false;
                    } else if (new == 0) {
                        //This is the correct next one, processing should be done
                        found = true;
                    } else {
                        log_error(EC_COMM_DROPPED_MESSAGE, 'x');
                        //This is an error, and a message was probably dropped somewhere
                        //Message should be processed anyway
                    }
                } else {
                    if (current + 1 == new) {
                        //New message with no missing messages, this is the normal operating point
                    } else if (new <= current) {
                        //Duplicate message, it should be ignored
                        return false;
                    } else {
                        log_error(EC_COMM_DROPPED_MESSAGE, 'x');
                        //Error state, message count increased with more than 1, probably dropped message
                        //Message should be processed anyway
                    }
                }
                peers[local_id].message_count = input->message_count;
                return true;
            }

        }
    }
    //ERROR when could not find
    return found;
}

void send_uart(u8 data, u8 skip_port) {
    if (skip_port != 1) send_data_uart_1(data);
    if (skip_port != 2) send_data_uart_2(data);
    if (skip_port != 3) send_data_uart_3(data);
    if (skip_port != 4) send_data_uart_4(data);

}

void send_intercom(u8 * data, u16 length, u8 skip_port) {

    send_on_the_fly(data, length, &send_uart, skip_port);

}

Mcu_uid get_uid_and_increment_counter() {
    u32 * uid_location = (u32*) UID_BASE;
    Mcu_uid uid = {
            uid_location[0],
            uid_location[1],
            uid_location[2],
            message_count++ };

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
void icom_read_message(u8 * buffer, u16 size, Icom_send * receive_buffer, u8 source_port) {
    bool in_process = false;
    Message_type processing = MT_ping;
    u8 bytes_remaining = 0;
    u8 byte_counter = 0;
    u8 sender_id_bytes_left = sizeof(Mcu_uid);
    bool do_processing = false;
    Mcu_uid * peer = NULL;

    loop(i, size)
    {
        if (sender_id_bytes_left) {
            ((u8 *) &receive_buffer->uid)[i] = buffer[i];
            sender_id_bytes_left--;
        } else if (!in_process) { //Start of a new struct
            receive_buffer->type = buffer[i];
            processing = buffer[i];
            //Check if we already know this module
            u16 index = mcu_uid_get_index(&receive_buffer->uid);
            //This means it is a new one, so we need to add it.
            if (index == 0xFFFF) { //new index
                index = mcu_uid_insert_first_empty(&receive_buffer->uid);
                if (index == 0xFFFF) {
                    //Out of peers, we don't know who sent this, ignore
                    do_processing = false;

                } else {
                    peer = &peers[index];
                    do_processing = true;
                }
            } else {
                //If we already know this pear check if it's not a duplicate message
                do_processing = mcu_uid_increment_count(index, &receive_buffer->uid);
                peer = &peers[index];
            }

            if (processing >= 8) {
                log_error(EC_COMM_UNKOWN_MESSAGE_STRUCTURE, buffer[i]);
                return;
            }
            bytes_remaining = message_size[processing];
            byte_counter = 0;
            in_process = true;

        } else {

            if (!bytes_remaining) {
                in_process = false;
            }

            bytes_remaining--;

            if (!do_processing) {
                continue;
            }

            switch (processing) {
            case MT_ping:
                break;
            DESERIALIZE_CASE(control_change)
                            DESERIALIZE_CASE(button_press)
                            DESERIALIZE_CASE(led_update)
                            default:
                log_error(EC_COMM_UNKOWN_MESSAGE_STRUCTURE, buffer[i]);
                return;
            }
        }
    }
}

