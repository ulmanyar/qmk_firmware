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

enum layers {
    _QWERTY = 0,
    _GAMING,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST,
};

// NOTE: Modify all tap-dance, keymaps etc. when disabling encoders
#ifdef ENCODER_ENABLE
// Encoder states
enum left_encoder_states {
    _RE_MEDIA,
    _RE_TABSWITCH,
    _NUMBER_OF_LRE_STATES,
};
enum left_encoder_states left_encoder_state = _RE_TABSWITCH;

enum right_encoder_states {
    _RE_SCROLL,
    _RE_CURSOR,
    _NUMBER_OF_RRE_STATES,
};
enum right_encoder_states right_encoder_state = _RE_SCROLL;

enum custom_keycodes {
    L_RE_ST = SAFE_RANGE,
    R_RE_ST,
};

// Used to define macros
// NOTE: Move out of #ifdef and create local #ifdef for rotary encoders when adding additional macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case L_RE_ST:
            // Modify functionality of left rotary encoder
            if (record->event.pressed) {
                // when keycode L_RE_ST is pressed
                left_encoder_state = (left_encoder_state + 1) % _NUMBER_OF_LRE_STATES;
            } else {
                // when keycode L_RE_ST is released
            }
            break;
        case R_RE_ST:
            // Modify functionality of right rotary encoder
            if (record->event.pressed) {
                // when keycode R_RE_ST is pressed
                right_encoder_state = (right_encoder_state + 1) % _NUMBER_OF_RRE_STATES;
            } else {
                // when keycode R_RE_ST is released
            }
            break;
        default:
            break;
    }
    return true;
};

// Used for tap-dance of left rotary encoder
void dance_left_re(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        left_encoder_state = (left_encoder_state + 1) % _NUMBER_OF_LRE_STATES;
    } else {
        switch (left_encoder_state) {
            case _RE_MEDIA:
                // Mute
                tap_code(KC_MUTE);
                break;
            case _RE_TABSWITCH:
                // Close tab
                tap_code16(C(SE_W));
                break;
            default:
                break;
        }
    }
    reset_tap_dance(state);
}

// Used for tap-dance of right rotary encoder
void dance_right_re(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        right_encoder_state = (right_encoder_state + 1) % _NUMBER_OF_RRE_STATES;
    } else {
        switch (right_encoder_state) {
            case _RE_SCROLL:
                // TBD
                break;
            case _RE_CURSOR:
                // Close window
                tap_code16(A(KC_F4));
                break;
            default:
                break;
        }
    }
    reset_tap_dance(state);
}

// Timer for accelerated scrolling
static uint16_t scroll_timer = 0;
static uint8_t scroll_step_size = 1;

bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        switch (left_encoder_state) {
            case _RE_MEDIA:
                // Volume control
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
            case _RE_TABSWITCH:
                // Switch tabs using Ctrl-Tab
                if (clockwise) {
                    tap_code16(C(KC_TAB));
                } else {
                    tap_code16(S(C(KC_TAB)));
                }
                break;
            default:
                break;
        }
    } else if (index == 1) {
        switch (right_encoder_state) {
            case _RE_CURSOR:
                // Move cursor one word to the left/right
                if (clockwise) {
                    tap_code16(C(KC_RGHT));
                } else {
                    tap_code16(C(KC_LEFT));
                }
                break;
            case _RE_SCROLL:
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
                        tap_code(KC_UP);
                    }
                } else {
                    for (uint8_t i = 0; i < scroll_step_size; i++) {
                        tap_code(KC_DOWN);
                    }
                }
                break;
            default:
                break;
        }
    }
    return false;
}
#endif

#ifdef BOTH_SHIFTS_TURNS_ON_CAPS_WORD
// Modified CAPS WORD for Swedish layout
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case SE_A ... SE_Z:
        case SE_ARNG:
        case SE_ADIA:
        case SE_ODIA:
        case SE_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case SE_1 ... SE_0:
        case KC_BSPC:
        case KC_DEL:
        case SE_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}
#endif

// Tap Dance declarations
enum {
    TD_ARNG_QUOT,
    TD_LREM_LREF,
    TD_RREM_RREF,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Å, twice for Caps Lock
    [TD_ARNG_QUOT] = ACTION_TAP_DANCE_DOUBLE(SE_ARNG, SE_QUOT),
    // Tap once for function switching, twice for function execution
    [TD_LREM_LREF] = ACTION_TAP_DANCE_FN(dance_left_re),
    [TD_RREM_RREF] = ACTION_TAP_DANCE_FN(dance_right_re),
};

// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define GAMING   DF(_GAMING)

// Layers
#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)

// Tap-dance
#define AA_QUOT  TD(TD_ARNG_QUOT)
#define L_RE_TAP TD(TD_LREM_LREF)
#define R_RE_TAP TD(TD_RREM_RREF)

// Mod-tap
#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_ADIA MT(MOD_RCTL, SE_ADIA)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)
#define RALT_ENT MT(MOD_RALT, KC_ENT)

// Windows Virtual Desktop Navigation
#define VD_NEW   G(C(SE_D))
#define VD_CLOSE G(C(KC_F4))
#define VD_LEFT  G(C(KC_LEFT))
#define VD_RIGHT G(C(KC_RIGHT))

// Custom tapping terms
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case R_RE_TAP:
        case L_RE_TAP:
            // Rotary encoders are slower to double-tap
            return TAPPING_TERM + 200;
        case CTL_ADIA:
            // Custom tapping term for Ä to avoid ^L
            return TAPPING_TERM + 50;
        default:
            return TAPPING_TERM;
    }
}


// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  | [   {  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |CapsLk|  |F-keys|  ] } |   N  |   M  | ,  ; | . :  | -  _ | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| Bksp | AltGr| Menu |
 *                        |      |      | Enter|      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB  , SE_Q ,  SE_W   ,  SE_E  ,   SE_R ,   SE_T ,                                          SE_Y ,   SE_U ,  SE_I ,   SE_O ,  SE_P , AA_QUOT,
     CTL_ESC , SE_A ,  SE_S   ,  SE_D  ,   SE_F ,   SE_G ,                                          SE_H ,   SE_J ,  SE_K ,   SE_L ,SE_ODIA,CTL_ADIA,
     KC_LSFT , SE_Z ,  SE_X   ,  SE_C  ,   SE_V ,   SE_B , KC_LBRC,KC_CAPS,     ADJUST , KC_RBRC,   SE_N ,   SE_M ,SE_COMM, SE_DOT ,SE_MINS, KC_RSFT,
                                // ADJUST , KC_LGUI, ALT_ENT, KC_SPC , NAV   ,     SYM    , KC_SPC ,KC_BSPC, KC_RALT, KC_APP
                               L_RE_TAP, KC_LGUI, ALT_ENT, FKEYS  , NAV   ,     SYM    , KC_SPC ,KC_BSPC, KC_RALT,R_RE_TAP
    ),

/*
 * Layer for gaming with ergo positions
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |   Q  |   W  |  E   |   R  |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |LShift|   A  |   S  |  D   |   F  |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | Ctrl |   Z  |   X  |  C   |   V  |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAMING] = LAYOUT(
      _______, _______,  SE_Q , SE_W   ,  SE_E  ,   SE_R,                                      _______, _______, _______, _______, _______, _______,
      _______, KC_LSFT,  SE_A , SE_S   ,  SE_D  ,   SE_F,                                      _______, _______, _______, _______, _______, _______,
      _______, KC_LCTL,  SE_Z , SE_X   ,  SE_C  ,   SE_V,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   ´  |   `  |   ^  |   ~  |   ¨  |                              | PgUp | Home |   ↑  | End  | VolUp| Sleep  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  GUI |  Alt | Ctrl | Shift|      |                              | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |ScLck |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |Delete|      |  |      |      |      | RGUI |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, SE_ACUT, SE_GRV , SE_CIRC, SE_TILD, SE_DIAE,                                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_SLEP,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,A(KC_F4),                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS,
      _______,VD_CLOSE, VD_LEFT,VD_RIGHT, VD_NEW , _______, _______, KC_SLCK, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                                 _______, _______, _______,_______, _______, _______, _______, KC_DEL  , _______, _______
    ),

/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |   +    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |    |   |   \  |  :   |  ;   |  -   |  [   |  {   |      |  |      |   }  |   ]  |  _   |  ,   |  .   |  /   |   ?    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |Delete|      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
     SE_SECT ,   SE_1 ,   SE_2 ,   SE_3 ,   SE_4 ,   SE_5 ,                                       SE_6 ,   SE_7 ,   SE_8 ,   SE_9 ,   SE_0 , SE_PLUS,
     SE_HALF , SE_EXLM, SE_DQUO, SE_HASH, SE_CURR, SE_PERC,                                     SE_AMPR, SE_SLSH, SE_LPRN, SE_RPRN, SE_EQL , SE_QUES,
     SE_LABK , SE_RABK, SE_AT  , SE_PND , SE_DLR , SE_PIPE, _______, _______, KC_RGUI, _______, SE_ASTR, SE_LCBR, SE_LBRC, SE_RBRC, SE_RCBR, SE_BSLS,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| Ctrl |  Alt |  GUI |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT(
      _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______,                                     _______, _______, _______, _______, _______, _______,
      _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |QWERTY|      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |Gaming|      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, QWERTY , _______, _______,                                    _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, GAMING , _______, _______,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
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

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        static const char PROGMEM layer_image[2][16] = {
            // 'layers', 16x16px
            {
                0x00, 0x20, 0xd0, 0x90, 0x08, 0x08, 0x04, 0x04, 0x02, 0x82, 0x81, 0x41, 0x42, 0x24, 0x68, 0x90,
            },
            {
                0x00, 0x09, 0x16, 0x24, 0x49, 0x92, 0x92, 0x49, 0x49, 0x24, 0x24, 0x12, 0x12, 0x09, 0x0b, 0x04,
            },
        };
        static const char PROGMEM encoder_image[2][16] = {
            // 'encoder', 16x16px
            {
                0x00, 0x00, 0x00, 0x00, 0xe0, 0x50, 0xd0, 0x88, 0x88, 0x88, 0xd0, 0x50, 0xe0, 0x00, 0x00, 0x00,
            },
            {
                0x00, 0x00, 0x00, 0x20, 0x53, 0x55, 0x86, 0xbd, 0xba, 0xbd, 0x86, 0x55, 0x53, 0x20, 0x00, 0x00
            },
        };
        // Write layer image
        oled_set_cursor(0, 0);
        oled_write_raw_P(layer_image[0], sizeof(layer_image[0]));
        oled_advance_page(false);
        oled_write_raw_P(layer_image[1], sizeof(layer_image[1]));
        // Write left encoder image
        oled_set_cursor(0, 2);
        oled_write_raw_P(encoder_image[0], sizeof(encoder_image[0]));
        oled_advance_page(false);
        oled_write_raw_P(encoder_image[1], sizeof(encoder_image[1]));
        int8_t x = 1;
        int8_t y = 24;
        oled_write_pixel(x, y, true);
        oled_write_pixel(x+1, y-1, true);
        oled_write_pixel(x+1, y+1, true);
        // Write right encoder image
        oled_set_cursor(0, 4);
        oled_write_raw_P(encoder_image[0], sizeof(encoder_image[0]));
        oled_advance_page(false);
        oled_write_raw_P(encoder_image[1], sizeof(encoder_image[1]));
        x = 15;
        y = 40;
        oled_write_pixel(x, y, true);
        oled_write_pixel(x-1, y-1, true);
        oled_write_pixel(x-1, y+1, true);

        // Host Keyboard Layer Status
        oled_set_cursor(4, 1);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("QWERTY\n"), false);
                break;
            case _GAMING:
                oled_write_P(PSTR("Gaming\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("Navigation\n"), false);
                break;
            case _SYM:
                oled_write_P(PSTR("Symbols\n"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        #ifdef ENCODER_ENABLE
        // Host Keyboard Left Rotary Encoder Status
        oled_set_cursor(4, 3);
        switch (left_encoder_state) {
            case _RE_MEDIA:
                oled_write_P(PSTR("Volume\n"), false);
                break;
            case _RE_TABSWITCH:
                oled_write_P(PSTR("Tabs\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }
        // Host Keyboard Right Rotary Encoder Status
        oled_set_cursor(4, 5);
        switch (right_encoder_state) {
            case _RE_SCROLL:
                oled_write_P(PSTR("Scroll\n"), false);
                break;
            case _RE_CURSOR:
                oled_write_P(PSTR("Cursor\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }
        #endif

        // Write host Keyboard LED Status to OLEDs
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

