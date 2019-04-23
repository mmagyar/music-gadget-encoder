#ifndef MCU_UTIL_LED_UPDATE_H_
#define MCU_UTIL_LED_UPDATE_H_
#include "../util/types.h"
#define intensity_gradients 5
//10 columns 4 levels
extern u16 led_data[10][intensity_gradients];

#define intensity_off       0b00000000
#define intensity_low       0b00000001
#define intensity_low_med   0b00000101
#define intensity_high_med  0b00010101
#define intensity_high      0b00011111

typedef enum {
    IN_OFF = intensity_off,
    IN_LOW = intensity_low,
    IN_LOW_MED = intensity_low_med,
    IN_HIGH_MED = intensity_high_med,
    IN_HIGH = intensity_high,
} Intensity;

typedef enum {
    DT_VALUE,
    DT_PRECISE
} Display_type;

typedef struct {
    Intensity green_precise[16];
    Intensity red_precise[16];
    u8 green_value;
    u8 red_value;
} Encoder_led;

typedef struct {
    Display_type display_type;
    u8 top_bar_value;
    Intensity top_bar_precise[32];
    Encoder_led encoders[4];
} Led_display;

Led_display display;
void led_calculate_bar_16(u8 value, Intensity * target);
void led_calculate_bar_signed_16(s8 signed_value, Intensity * target) ;
void update_display();

#endif /* MCU_UTIL_LED_UPDATE_H_ */
