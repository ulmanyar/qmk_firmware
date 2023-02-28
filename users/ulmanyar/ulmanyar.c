#include "ulmanyar.h"


// Custom tapping terms
#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SYM_SPC:
            return TAPPING_TERM + 25;
        default:
            return TAPPING_TERM;
    }
}
#endif // TAPPING_TERM_PER_KEY

// Custom retro tapping
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NAV_ENT:
        case SFT_ESC:
            return false;
        default:
            return true;
    }
}

// Utility function to write modifier states to OLEDs
void render_mod_state(
    uint16_t *mod_state,
    uint16_t mod_mask,
    char mod_indicator,
    uint8_t x,
    uint8_t y
) {
    static char modstr[] = " ";
    oled_set_cursor(x, y);
    modstr[0] = *mod_state & mod_mask ? mod_indicator : ' ';
    oled_write(modstr, false);
}


void render_layer_state() {
    switch (get_highest_layer(layer_state|default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QWERTY\n"), false);
            break;
        case _COLEMAK_DH:
            oled_write_P(PSTR("Colemak DH\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("Numbers\n"), false);
            break;
        case _SYM:
            oled_write_P(PSTR("Symbols\n"), false);
            break;
        case _MED:
            oled_write_P(PSTR("Media\n"), false);
            break;
        case _RGB:
            oled_write_P(PSTR("RGB\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }
}

// Utility function to write encoder state to current position
void render_encoder_state(enum encoder_states current_state) {
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
}


// Utility function to execute encoder functionality based on encoder_states
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
                tap_code(KC_WH_D);
            } else {
                tap_code(KC_WH_U);
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


// *** Callum mods and (modified) swapper support code ***
bool is_swapper_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case KC_LSFT:
    case KC_RSFT:
    case OS_SHFT:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_cancel_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    // Separate tap/hold for all layer/mod tap keys
    case SFT_ESC:
    case NAV_ENT:
    case NUM_BSP:
        if (record->tap.count > 0) {
            // Process taps
            return false;
        } else {
            // Cancel on hold
            return true;
        }
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    // Separate tap/hold for all layer/mod tap keys
    case SFT_ESC:
    case NAV_ENT:
    case NUM_BSP:
        if (record->tap.count > 0) {
            // Process taps
            return false;
        } else {
            // Ignore holds
            return true;
        }
    // Ignore mods
    case KC_LSFT:
    case KC_RSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
        return true;
    default:
        return false;
    }
}
