
#pragma once
#include QMK_KEYBOARD_H

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


void oled_write_encoder_state(enum encoder_states current_state);

void encoder_functions(enum encoder_states current_state, bool clockwise);
