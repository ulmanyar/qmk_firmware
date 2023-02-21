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
static enum encoder_states re_states[] = {_TABSWITCH, _VOLUME};
static size_t number_of_re_states = sizeof(re_states) / sizeof(re_states[0]);
static uint8_t current_re_state = 0;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 3) {
        encoder_functions(re_states[current_re_state], clockwise);
    }
    return false;
}
#endif // ENCODER_ENABLE


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


// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
#ifdef ENCODER_ENABLE
        SE_Q  ,  SE_W  ,  SE_E  ,  SE_R  ,  SE_T  ,  SE_Y  ,  SE_U  ,  SE_I  ,  SE_O  , S_RE_ST,
#else
        SE_Q  ,  SE_W  ,  SE_E  ,  SE_R  ,  SE_T  ,  SE_Y  ,  SE_U  ,  SE_I  ,  SE_O  , XXXXXXX,
#endif // ENCODER_ENABLE
        SE_A  ,  SE_S  ,  SE_D  ,  SE_F  ,  SE_G  ,  SE_H  ,  SE_J  ,  SE_K  ,  SE_L  ,  SE_P  ,
        SE_Z  ,  SE_X  ,  SE_C  ,  SE_V  ,  SE_B  ,  SE_N  ,  SE_M  ,SE_COMM , SE_DOT ,SE_MINS ,
                                  NAV_ENT, SFT_ESC, SYM_SPC, NUM_BSP
    ),

    [_COLEMAK_DH] = LAYOUT(
#ifdef ENCODER_ENABLE
        SE_Q  ,  SE_W  ,  SE_F  ,   SE_P ,   SE_B ,  SE_J  ,  SE_L  ,  SE_U  ,  SE_Y  , S_RE_ST,
#else
        SE_Q  ,  SE_W  ,  SE_F  ,   SE_P ,   SE_B ,  SE_J  ,  SE_L  ,  SE_U  ,  SE_Y  , XXXXXXX,
#endif // ENCODER_ENABLE
        SE_A  ,  SE_R  ,  SE_S  ,   SE_T ,   SE_G ,  SE_M  ,  SE_N  ,  SE_E  ,  SE_I  ,  SE_O  ,
        SE_Z  ,  SE_X  ,  SE_C  ,   SE_D ,   SE_V ,  SE_K  ,  SE_H  ,SE_COMM , SE_DOT ,SE_MINS ,
#ifdef ENCODER_ENABLE
                                  NAV_ENT, SFT_ESC, SYM_SPC, NUM_BSP
#else
                                XXXXXXX , XXXXXXX, NAV_ENT, SFT_ESC, XXXXXXX, XXXXXXX, SYM_SPC, NUM_BSP, XXXXXXX,XXXXXXX
#endif // ENCODER_ENABLE
    ),

    [_NAV] = LAYOUT(
    // Missing: Media buttons, *LCK
       SW_WIN , SW_TAB , _______, KC_LGUI, KC_SLEP, KC_HOME, KC_PGDN, KC_PGUP, KC_END , _______,
       OS_GUI , OS_ALT , OS_CTRL, OS_SHFT,A(KC_F4), KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, SE_ARNG,
      VD_CLOSE, VD_LEFT,VD_RIGHT, VD_NEW , DL_TOGG, KC_PSCR, KC_TAB , KC_INS , SE_ODIA, SE_ADIA,
                                  _______, _______, KC_DEL , KC_BSPC

    ),

    [_NUM] = LAYOUT(
        SE_1  ,  SE_2  ,  SE_3  ,  SE_4  ,  SE_5  ,  SE_6  ,  SE_7  ,  SE_8  ,  SE_9  , _______,
       OS_GUI , OS_ALT , OS_CTRL, OS_SHFT, KC_F11 , KC_F12 , OS_SHFT, OS_CTRL, OS_ALT , OS_GUI ,
       KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,
                                   SE_0  , _______, _______, _______
    ),

    [_SYM] = LAYOUT(
    // Missing: §, ½, *LCK
       SE_ACUT, SE_GRV , SE_CIRC, SE_TILD, SE_DIAE, SE_QUOT, SE_BSLS, SE_LABK, SE_RABK, _______,
       SE_EXLM, SE_DQUO, SE_HASH, SE_CURR, SE_PERC, SE_AMPR, SE_SLSH, SE_LPRN, SE_RPRN, SE_EQL ,
       SE_QUES, SE_AT  , SE_PND , SE_DLR , SE_PIPE, SE_ASTR, SE_LCBR, SE_LBRC, SE_RBRC, SE_RCBR,
                                  SE_PLUS, KC_CAPS, _______, _______
    ),

//     [_LAYERINDEX] = LAYOUT(
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
