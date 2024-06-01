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
#include "keycodes.h"
#include QMK_KEYBOARD_H
#include "keymap_swedish.h"
#include "ulmanyar.h"
#include "combos.inc"
#include "oneshot.h"
#include "swapper.h"
#include "wrappers.h"

// NOTE: Modify all tap-dance, keymaps etc. when disabling encoders
#ifdef ENCODER_ENABLE
// Encoder states
static enum encoder_states re_states[] = {_TABSWITCH, _WORDCURSOR, _VOLUME};
static size_t number_of_re_states = sizeof(re_states) / sizeof(re_states[0]);
static uint8_t current_re_state = 0;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 3) {
        encoder_functions(re_states[current_re_state], clockwise);
    }
    return false;
}
#endif // ENCODER_ENABLE


// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_wrapper(
#ifdef ENCODER_ENABLE
       _________________QWERTY_L1_________________,  SE_Y  ,  SE_U  ,  SE_I  ,  SE_O  , S_RE_ST,
#else
       _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
#endif // ENCODER_ENABLE
       _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
       _________________QWERTY_L3_________________, _________________QWERTY_R3_________________,
                                 MO(_NAV), SFT_ESC, KC_SPC , MO(_NUM)
    ),

    [_COLEMAK_DH] = LAYOUT_wrapper(
#ifdef ENCODER_ENABLE
       ______________COLEMAK_MOD_DH_L1____________,  SE_J  ,  SE_L  ,  SE_U  ,  SE_Y  , S_RE_ST,
#else
       ______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________,
#endif // ENCODER_ENABLE
       ______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________,
       ______________COLEMAK_MOD_DH_L3____________, ______________COLEMAK_MOD_DH_R3____________,
                                 MO(_NAV), SFT_ESC, SYM_SPC, MO(_NUM)
    ),

    [_NAV] = LAYOUT_wrapper(
    // Missing: Media buttons, *LCK
       ________________NAVIGATION_L1______________, ________________NAVIGATION_R1______________,
       ________________NAVIGATION_L2______________, ________________NAVIGATION_R2______________,
       ________________NAVIGATION_L3______________, ________________NAVIGATION_R3______________,
                                  _______,A(KC_F4), KC_BSPC, KC_DEL

    ),

    [_SYM] = LAYOUT_wrapper(
       __________________SYMBOL_L1________________, __________________SYMBOL_R1________________,
       __________________SYMBOL_L2________________, __________________SYMBOL_R2________________,
       __________________SYMBOL_L3________________, __________________SYMBOL_R3________________,
                                  SE_PLUS, KC_CAPS, _______, _______
    ),

    [_NUM] = LAYOUT_wrapper(
       __________________NUMBER_L1________________, __________________NUMBER_R1________________,
       __________________NUMBER_L2________________, __________________NUMBER_R2________________,
       __________________NUMBER_L3________________, __________________NUMBER_R3________________,
                                   SE_0  , SE_DOT , NUM_TOG, _______
    ),

    [_FUN] = LAYOUT_wrapper(
       _________________FUNCTION_L1_______________, _________________FUNCTION_R1_______________,
       _________________FUNCTION_L2_______________, _________________FUNCTION_R2_______________,
       _________________FUNCTION_L3_______________, _________________FUNCTION_R3_______________,
                                  _______, _______, _______, _______
    ),

    [_ADJ] = LAYOUT_wrapper(
       KC_SLEP, KC_NUM , KC_CAPS, KC_SCRL, _______, RGB_TOG, DL_TOGG, _______, _______, KC_MUTE,
       _______, _______, _______, _______, _______, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,
       _______,TG(_ADJ), _______, _______, _______,RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,
                                  _______, _______, _______, _______
    ),
//     [_LAYERINDEX] = LAYOUT_wrapper(
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______
//     ),
};
// clang-format on

bool swap_windows_active = false;
bool swap_tabs_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _NUM, _FUN, _FUN);
  state = update_tri_layer_state(state, _NAV, _ADJ, _ADJ);
  return state;
}

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


    static bool num_layer_locked = false;
    switch (keycode) {
        case NUM_TOG:
            if (record->event.pressed) {
                if (num_layer_locked) {
                    layer_off(_NUM);
                    num_layer_locked = false;
                } else {
                    num_layer_locked = true;
                }
                return false;
            }
        case MO(_NUM):
            if (!record->event.pressed && num_layer_locked) {
                num_layer_locked = false;
                return false;
            } else {
                num_layer_locked = false;
                return true;
            }
        case DL_TOGG:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY + _COLEMAK_DH - get_highest_layer(default_layer_state));
            }
            return false;
        case S_RE_ST:
            #ifdef ENCODER_ENABLE
            // Modify functionality of left rotary encoder
            if (record->event.pressed) {
                // when keycode S_RE_ST is pressed
                current_re_state = (current_re_state + 1) % number_of_re_states;
            } else {
                // when keycode S_RE_ST is released
            }
            #endif // ENCODER_ENABLE
            break;
        default:
            break;
    }
    return true;
};

void keyboard_pre_init_user(void) {
  // Set Liatris LED pin as output
  setPinOutput(24);
  // Turn the LED off
  // (Due to technical reasons, high is off and low is on)
  writePinHigh(24);
}
