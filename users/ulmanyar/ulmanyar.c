#include "ulmanyar.h"

void oled_write_encoder_state(enum encoder_states current_state) {
    switch (current_state) {
        case _VOLUME:
            oled_write_P(PSTR("Volume\n"), false);
            break;
        case _TABSWITCH:
            oled_write_P(PSTR("Tabs\n"), false);
            break;
        case _WINSWITCH:
            oled_write_P(PSTR("Windows\n"), false);
            break;
        case _ARROWSCROLL:
        case _MOUSESCROLL:
            oled_write_P(PSTR("Scroll\n"), false);
            break;
        case _WORDCURSOR:
            oled_write_P(PSTR("Cursor\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }
};