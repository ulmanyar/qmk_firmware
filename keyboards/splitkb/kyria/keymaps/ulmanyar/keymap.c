/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "keymap_swedish.h"
#include "ulmanyar.h"
#include "oneshot.h"
#include "swapper.h"

// NOTE: Modify all tap-dance, keymaps etc. when disabling encoders
#ifdef ENCODER_ENABLE
// Encoder states
static enum encoder_states lre_states[] = {_TABSWITCH, _VOLUME};
static size_t number_of_lre_states = sizeof(lre_states) / sizeof(lre_states[0]);
static uint8_t current_lre_state = 0;

static enum encoder_states rre_states[] = {_ARROWSCROLL, _WORDCURSOR};
static size_t number_of_rre_states = sizeof(rre_states) / sizeof(rre_states[0]);
static uint8_t current_rre_state = 0;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        encoder_functions(lre_states[current_lre_state], clockwise);
    } else if (index == 1) {
        encoder_functions(rre_states[current_rre_state], clockwise);
    }
    return false;
}
#endif // ENCODER_ENABLE


// Aliases for readability
// Layer-tap
#define NAV_ENT  LT(_NAV, KC_ENT)
#define SYM_SPC  LT(_SYM, KC_SPC)
#define NUM_BSP  LT(_NUM, KC_BSPC)

// Mod-tap
#define SFT_ESC  MT(MOD_LSFT, KC_ESC)

// Windows Virtual Desktop Navigation
#define VD_NEW   G(C(SE_D))
#define VD_CLOSE G(C(KC_F4))
#define VD_LEFT  G(C(KC_LEFT))
#define VD_RIGHT G(C(KC_RIGHT))

// Custom tapping terms
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SYM_SPC:
            return TAPPING_TERM + 25;
        default:
            return TAPPING_TERM;
    }
}

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


// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
    // Missing: *LCK, RAlt
      XXXXXXX,  SE_Q  ,  SE_W  ,  SE_E  ,  SE_R  ,  SE_T  ,                                      SE_Y  ,  SE_U  ,  SE_I  ,  SE_O  ,  SE_P  , XXXXXXX,
      XXXXXXX,  SE_A  ,  SE_S  ,  SE_D  ,  SE_F  ,  SE_G  ,                                      SE_H  ,  SE_J  ,  SE_K  ,  SE_L  ,SE_ODIA , XXXXXXX,
      XXXXXXX,  SE_Z  ,  SE_X  ,  SE_C  ,  SE_V  ,  SE_B  , _______, _______, _______, _______,  SE_N  ,  SE_M  ,SE_COMM , SE_DOT ,SE_MINS , XXXXXXX,
                                L_RE_ST , _______, NAV_ENT, SFT_ESC, _______, _______, SYM_SPC, NUM_BSP, _______,R_RE_ST
    ),

    [_COLEMAK_DH] = LAYOUT(
    // Missing: *LCK, RAlt
      XXXXXXX,  SE_Q  ,  SE_W  ,  SE_F  ,   SE_P ,   SE_B ,                                      SE_J  ,  SE_L  ,  SE_U  ,  SE_Y  ,SE_ODIA , XXXXXXX,
      XXXXXXX,  SE_A  ,  SE_R  ,  SE_S  ,   SE_T ,   SE_G ,                                      SE_M  ,  SE_N  ,  SE_E  ,  SE_I  ,  SE_O  , XXXXXXX,
      XXXXXXX,  SE_Z  ,  SE_X  ,  SE_C  ,   SE_D ,   SE_V , _______, _______, _______, _______,  SE_K  ,  SE_H  ,SE_COMM , SE_DOT ,SE_MINS , XXXXXXX,
                                L_RE_ST , _______, NAV_ENT, SFT_ESC, _______, _______, SYM_SPC, NUM_BSP, _______,R_RE_ST
    ),

    [_NAV] = LAYOUT(
    // Missing: Media buttons, *LCK
      _______, SW_WIN , SW_TAB , _______, KC_LGUI, KC_SLEP,                                     KC_HOME, KC_PGDN, KC_PGUP, KC_END , SE_ARNG, _______,
      _______, OS_GUI , OS_ALT , OS_CTRL, OS_SHFT,A(KC_F4),                                     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, SE_ADIA, _______,
      _______,VD_CLOSE, VD_LEFT,VD_RIGHT, VD_NEW , DL_TOGG, _______, _______, _______, _______, KC_PSCR, KC_TAB , _______, KC_INS , _______, _______,
                                 _______, _______, _______, _______, _______, _______, KC_DEL , KC_BSPC, _______, _______

    ),

    [_NUM] = LAYOUT(
      _______,  SE_1  ,  SE_2  ,  SE_3  ,  SE_4  ,  SE_5  ,                                      SE_6  ,  SE_7  ,  SE_8  ,  SE_9  ,  SE_0  , _______,
      _______, OS_GUI , OS_ALT , OS_CTRL, OS_SHFT, KC_F11 ,                                     KC_F12 , OS_SHFT, OS_CTRL, OS_ALT , OS_GUI , _______,
      _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______, _______, _______, _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_SYM] = LAYOUT(
    // Missing: §, ½, *LCK
      _______, SE_ACUT, SE_GRV , SE_CIRC, SE_TILD, SE_DIAE,                                     SE_QUOT, SE_BSLS, SE_LABK, SE_RABK, SE_PLUS, _______,
      _______, SE_EXLM, SE_DQUO, SE_HASH, SE_CURR, SE_PERC,                                     SE_AMPR, SE_SLSH, SE_LPRN, SE_RPRN, SE_EQL , _______,
      _______, SE_QUES, SE_AT  , SE_PND , SE_DLR , SE_PIPE, _______, _______, _______, _______, SE_ASTR, SE_LCBR, SE_LBRC, SE_RBRC, SE_RCBR, _______,
                                 _______, _______, _______, KC_CAPS, _______, _______, _______, _______, _______, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};
// clang-format on

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

bool swap_windows_active = false;
bool swap_tabs_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;


// User level override of process_record, used to define macros etc.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &swap_windows_active, KC_LALT, KC_TAB, SW_WIN,
        keycode, record
    );

    update_swapper(
        &swap_tabs_active, KC_LCTL, KC_TAB, SW_TAB,
        keycode, record
    );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LGUI, OS_GUI,
        keycode, record
    );


    switch (keycode) {
        case DL_TOGG:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY + _COLEMAK_DH - get_highest_layer(default_layer_state));
            }
            return false;
        case L_RE_ST:
            // Modify functionality of left rotary encoder
            if (record->event.pressed) {
                // when keycode L_RE_ST is pressed
                current_lre_state = (current_lre_state + 1) % number_of_lre_states;
            } else {
                // when keycode L_RE_ST is released
            }
            break;
        case R_RE_ST:
            // Modify functionality of right rotary encoder
            if (record->event.pressed) {
                // when keycode R_RE_ST is pressed
                current_rre_state = (current_rre_state + 1) % number_of_rre_states;
            } else {
                // when keycode R_RE_ST is released
            }
            break;
        default:
            break;
    }
    return true;
};

// Utility function to write modifier states to OLEDs
void write_mod_state(
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
/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }
static uint16_t mod_state = 0;
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // *** Host Keyboard States ***
        // Define layer image
        static const char PROGMEM layer_image[2][16] = {
            // 'layers', 16x16px
            {
                0x00, 0x20, 0xd0, 0x90, 0x08, 0x08, 0x04, 0x04, 0x02, 0x82, 0x81, 0x41, 0x42, 0x24, 0x68, 0x90,
            },
            {
                0x00, 0x09, 0x16, 0x24, 0x49, 0x92, 0x92, 0x49, 0x49, 0x24, 0x24, 0x12, 0x12, 0x09, 0x0b, 0x04,
            },
        };
        // Write layer image
        oled_set_cursor(0, 0);
        oled_write_raw_P(layer_image[0], sizeof(layer_image[0]));
        oled_advance_page(false);
        oled_write_raw_P(layer_image[1], sizeof(layer_image[1]));
        // Write host keyboard layer state to OLEDs
        oled_set_cursor(4, 1);
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
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        #ifdef ENCODER_ENABLE
        // Define encoder image
        static const char PROGMEM encoder_image[2][16] = {
            // 'encoder', 16x16px
            {
                0x00, 0x00, 0x00, 0x00, 0xe0, 0x50, 0xd0, 0x88, 0x88, 0x88, 0xd0, 0x50, 0xe0, 0x00, 0x00, 0x00,
            },
            {
                0x00, 0x00, 0x00, 0x20, 0x53, 0x55, 0x86, 0xbd, 0xba, 0xbd, 0x86, 0x55, 0x53, 0x20, 0x00, 0x00
            },
        };

        // Write left encoder image to OLEDs
        oled_set_cursor(0, 2);
        oled_write_raw_P(encoder_image[0], sizeof(encoder_image[0]));
        oled_advance_page(false);
        oled_write_raw_P(encoder_image[1], sizeof(encoder_image[1]));
        int8_t x = 17;
        int8_t y = 24;
        oled_write_pixel(x+2, y,   true);
        oled_write_pixel(x+1, y+1, true);
        oled_write_pixel(x,   y+2, true);
        oled_write_pixel(x+1, y+3, true);
        oled_write_pixel(x+2, y+4, true);
        // Write right encoder image to OLEDs
        oled_set_cursor(0, 4);
        oled_write_raw_P(encoder_image[0], sizeof(encoder_image[0]));
        oled_advance_page(false);
        oled_write_raw_P(encoder_image[1], sizeof(encoder_image[1]));
        x = 18;
        y = 40;
        oled_write_pixel(x,   y,   true);
        oled_write_pixel(x+1, y+1, true);
        oled_write_pixel(x+2, y+2, true);
        oled_write_pixel(x+1, y+3, true);
        oled_write_pixel(x,   y+4, true);
        // Write left rotary encoder state to OLEDs
        oled_set_cursor(4, 3);
        oled_write_encoder_state(lre_states[current_lre_state]);
        // Write right rotary encoder state to OLEDs
        oled_set_cursor(4, 5);
        oled_write_encoder_state(rre_states[current_rre_state]);
        #endif

        // Write mod status to OLEDs
        mod_state = get_mods();
        write_mod_state(&mod_state, MOD_BIT(KC_LSFT), 0x18, 16, 2);
        write_mod_state(&mod_state, MOD_BIT(KC_LCTL), 0x5E, 18, 2);
        write_mod_state(&mod_state, MOD_BIT(KC_LALT), 0x25, 16, 4);
        write_mod_state(&mod_state, MOD_BIT(KC_LGUI), 0x04, 18, 4);

        // Write host keyboard LED state to OLEDs
        oled_set_cursor(0, 7);
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        #ifdef DISPLAY_KYRIA_LOGO
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
        #else
        oled_write_P(PSTR("NO LOGO"), false);
        #endif
    }
    return false;
}
#endif

