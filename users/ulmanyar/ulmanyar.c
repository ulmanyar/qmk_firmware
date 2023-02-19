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


void encoder_functions(enum encoder_states current_state, bool clockwise) {
    // Timer for accelerated scrolling
    static uint16_t scroll_timer = 0;
    static uint8_t scroll_step_size = 1;

    switch (current_state) {
        case _VOLUME:
            // Volume control
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        case _TABSWITCH:
            // Switch tabs using Ctrl-Tab
            if (clockwise) {
                tap_code16(C(KC_TAB));
            } else {
                tap_code16(S(C(KC_TAB)));
            }
            break;
        case _WINSWITCH:
            // Not yet implemented
            break;
        case _ARROWSCROLL:
            // Scroll up/down with accelerated speed
            if (timer_elapsed(scroll_timer) < ACCSCROLL_REPEAT_INTERVAL) {
                scroll_step_size += ACCSCROLL_STEP_SIZE;
                scroll_step_size = (scroll_step_size > ACCSCROLL_MAX_STEP) ? ACCSCROLL_MAX_STEP : scroll_step_size;
            } else {
                scroll_step_size = 1;
            }
            scroll_timer = timer_read();

            if (clockwise) {
                for (uint8_t i = 0; i < scroll_step_size; i++) {
                    tap_code(KC_DOWN);
                }
            } else {
                for (uint8_t i = 0; i < scroll_step_size; i++) {
                    tap_code(KC_UP);
                }
            }
            break;
        case _MOUSESCROLL:
            #ifdef MOUSEKEY_ENABLE
            if (clockwise) {
                tap_code(KC_WH_D)
            } else {
                tap_code(KC_WH_U)
            }
            #endif
            break;
        case _WORDCURSOR:
            // Move cursor one word to the left/right
            if (clockwise) {
                tap_code16(C(KC_RGHT));
            } else {
                tap_code16(C(KC_LEFT));
            }
            break;
        default:
            break;
    }
}
