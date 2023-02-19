
#pragma once
#include QMK_KEYBOARD_H
#include "keymap_swedish.h"

#define ACCSCROLL_MAX_STEP 18
#define ACCSCROLL_STEP_SIZE 3
#define ACCSCROLL_REPEAT_INTERVAL 75

enum layers {
    _QWERTY = 0,
    _COLEMAK_DH,
    _NAV,
    _NUM,
    _SYM,
    _MED,
    _RGB,
};

enum encoder_states {
    _VOLUME = 0,
    _TABSWITCH,
    _WINSWITCH,
    _ARROWSCROLL,
    _MOUSESCROLL,
    _WORDCURSOR,
};

enum custom_keycodes {
    L_RE_ST = SAFE_RANGE,
    R_RE_ST,

    DL_TOGG,

    SW_WIN,
    SW_TAB,

    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_GUI,
};

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

void write_mod_state(
    uint16_t *mod_state,
    uint16_t mod_mask,
    char mod_indicator,
    uint8_t x,
    uint8_t y
);

void oled_write_layer_state(void);

void oled_write_encoder_state(enum encoder_states current_state);

void encoder_functions(enum encoder_states current_state, bool clockwise);
