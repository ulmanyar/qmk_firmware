#include "keycodes.h"
#include "keymap_swedish.h"
#include QMK_KEYBOARD_H
#include "ulmanyar.h"
#include "combos.inc"
#include "oneshot.h"
#include "swapper.h"
#include "wrappers.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Layer 0
     * ,-----------------------------------------------------------------------------------.
     * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl |  GUI | Caps |  Alt |Layer1|    Space    |Layer2|  /   | Left | Down |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_planck_mit_wrapper(
        KC_ESC , _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, SE_ADIA,
        KC_TAB , _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, SE_ODIA,
        KC_LSFT, _________________QWERTY_L3_________________, _________________QWERTY_R3_________________, KC_RSFT,
        KC_LCTL, KC_LGUI,MO(_ADJ),MO(_SYM),MO(_NAV),      KC_SPC,     MO(_NUM),MO(_FUN), KC_CAPS, KC_APP , KC_RCTL
    ),

    [_COLEMAK_DH] = LAYOUT_planck_mit_wrapper(
        KC_ESC , ______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________, SE_ADIA,
        KC_TAB , ______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________, SE_ODIA,
        KC_LSFT, ______________COLEMAK_MOD_DH_L3____________, ______________COLEMAK_MOD_DH_R3____________, KC_RSFT,
        KC_LCTL, KC_LGUI,MO(_RGB),MO(_SYM),MO(_NAV),      KC_SPC,     MO(_NUM),MO(_FUN), KC_CAPS, KC_APP , KC_RCTL
    ),

    /* Layer 1
     * ,-----------------------------------------------------------------------------------.
     * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      | Vol- | Vol+ | Mute |      |      |      |  F11 |  F12 |      |      |      |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Reset|      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_NAV] = LAYOUT_planck_mit_wrapper(
        XXXXXXX, ________________NAVIGATION_L1______________, ________________NAVIGATION_R1______________, XXXXXXX,
        XXXXXXX, ________________NAVIGATION_L2______________, ________________NAVIGATION_R2______________, XXXXXXX,
        XXXXXXX, ________________NAVIGATION_L3______________, ________________NAVIGATION_R3______________, XXXXXXX,
        XXXXXXX, _______, _______, _______,A(KC_F4),     _______,      KC_BSPC, KC_DEL , _______, _______, XXXXXXX
    ),

    /* Layer 2 (r_ Indicates RGB Controls)
     * ,-----------------------------------------------------------------------------------.
     * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |r_TOG |r_Mode|r_Hue+|r_Hue-|      |      |   -  |   =  |   [  |   ]  |  \   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |BL_TOG|BL_STEP|     |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_SYM] = LAYOUT_planck_mit_wrapper(
        XXXXXXX, __________________SYMBOL_L1________________, __________________SYMBOL_R1________________, XXXXXXX,
        XXXXXXX, __________________SYMBOL_L2________________, __________________SYMBOL_R2________________, XXXXXXX,
        XXXXXXX, __________________SYMBOL_L3________________, __________________SYMBOL_R3________________, XXXXXXX,
        XXXXXXX, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, XXXXXXX
    ),

    [_NUM] = LAYOUT_planck_mit_wrapper(
        XXXXXXX, __________________NUMBER_L1________________, __________________NUMBER_R1________________, XXXXXXX,
        XXXXXXX, __________________NUMBER_L2________________, __________________NUMBER_R2________________, XXXXXXX,
        XXXXXXX, __________________NUMBER_L3________________, __________________NUMBER_R3________________, XXXXXXX,
        XXXXXXX, _______, _______, SE_COMM,  SE_0  ,     SE_DOT ,      _______, _______, _______, _______, XXXXXXX
    ),

    [_FUN] = LAYOUT_planck_mit_wrapper(
        XXXXXXX, _________________FUNCTION_L1_______________, _________________FUNCTION_R1_______________, XXXXXXX,
        XXXXXXX, _________________FUNCTION_L2_______________, _________________FUNCTION_R2_______________, XXXXXXX,
        XXXXXXX, _________________FUNCTION_L3_______________, _________________FUNCTION_R3_______________, XXXXXXX,
        XXXXXXX, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, XXXXXXX
    ),

    [_RGB] = LAYOUT_planck_mit_wrapper(
        XXXXXXX, __________________ADJUST_L1________________, __________________ADJUST_R1________________, XXXXXXX,
        XXXXXXX, __________________ADJUST_L2________________, __________________ADJUST_R2________________, XXXXXXX,
        XXXXXXX, __________________ADJUST_L3________________, __________________ADJUST_R3________________, XXXXXXX,
        XXXXXXX, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, XXXXXXX
    ),
};

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
        default:
            break;
    }
    return true;
}
