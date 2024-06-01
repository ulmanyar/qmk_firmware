#pragma once
#include "keycodes.h"
#include "ulmanyar.h"
#include "keymap_swedish.h"

#define LAYOUT_wrapper(...)   LAYOUT(__VA_ARGS__)
#define LAYOUT_planck_mit_wrapper(...)   LAYOUT_planck_mit(__VA_ARGS__)

// clang-format off

#define _________________QWERTY_L1_________________       SE_Q,    SE_W,    SE_E,    SE_R,    SE_T
#define _________________QWERTY_L2_________________       SE_A,    SE_S,    SE_D,    SE_F,    SE_G
#define _________________QWERTY_L3_________________       SE_Z,    SE_X,    SE_C,    SE_V,    SE_B

#define _________________QWERTY_R1_________________       SE_Y,    SE_U,    SE_I,    SE_O,    XXXXXXX
#define _________________QWERTY_R2_________________       SE_H,    SE_J,    SE_K,    SE_L,    SE_P
#define _________________QWERTY_R3_________________       SE_N,    SE_M,    SE_COMM, SE_DOT,  SE_MINS


#define ______________COLEMAK_MOD_DH_L1____________     SE_Q,   SE_W,   SE_F,   SE_P,   SE_B
#define ______________COLEMAK_MOD_DH_L2____________     SE_A,   SE_R,   SE_S,   SE_T,   SE_G
#define ______________COLEMAK_MOD_DH_L3____________     SE_Z,   SE_X,   SE_C,   SE_D,   SE_V

#define ______________COLEMAK_MOD_DH_R1____________     SE_J,   SE_L,   SE_U,   SE_Y,   SE_ARNG
#define ______________COLEMAK_MOD_DH_R2____________     SE_M,   SE_N,   SE_E,   SE_I,   SE_O
#define ______________COLEMAK_MOD_DH_R3____________     SE_K,   SE_H,   SE_COMM,SE_DOT, SE_MINS


#define ________________NAVIGATION_L1______________  A(KC_LEFT), SW_WIN , SW_TAB ,VD_RIGHT, KC_LGUI
#define ________________NAVIGATION_L2______________     OS_GUI , OS_ALT , OS_CTRL, OS_SHFT, _______
#ifdef TWO_THUMBS
#define ________________NAVIGATION_L3______________     _______,TG(_ADJ),_______, DL_TOGG, VD_NEW
#else
#define ________________NAVIGATION_L3______________     _______, _______, _______, DL_TOGG, VD_NEW
#endif

#define ________________NAVIGATION_R1______________     KC_HOME, KC_PGDN, KC_PGUP, KC_END , _______
#define ________________NAVIGATION_R2______________     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______
#define ________________NAVIGATION_R3______________     KC_PSCR, KC_INS , SE_ODIA, SE_ADIA, SE_ARNG


#define __________________SYMBOL_L1________________     SE_PND , SE_EXLM, SE_LABK, SE_LBRC, SE_SLSH
#define __________________SYMBOL_L2________________     SE_CURR, SE_DQUO, SE_LCBR, SE_LPRN, SE_PERC
#define __________________SYMBOL_L3________________     SE_PIPE, SE_AT  , SE_HASH, SE_DLR , SE_PIPE

#define __________________SYMBOL_R1________________     SE_BSLS, SE_RBRC, SE_RABK, SE_QUES, SE_PLUS
#define __________________SYMBOL_R2________________     SE_AMPR, SE_RPRN, SE_RCBR, SE_QUOT, SE_EQL
#define __________________SYMBOL_R3________________     SE_MINS, SE_PLUS, SE_EQL , SE_ASTR, SE_UNDS


#define __________________NUMBER_L1________________     _______,  SE_7  ,  SE_8  ,  SE_9  , SE_PLUS
#define __________________NUMBER_L2________________     SE_SLSH,  SE_4  ,  SE_5  ,  SE_6  , SE_EQL
#define __________________NUMBER_L3________________     SE_ASTR,  SE_1  ,  SE_2  ,  SE_3  , SE_MINS

#define __________________NUMBER_R1________________     SE_ACUT, SE_CIRC, SE_TILD, SE_DIAE, _______
#define __________________NUMBER_R2________________     SE_GRV , OS_SHFT, OS_CTRL, OS_ALT , OS_GUI
#ifdef TWO_THUMBS
#define __________________NUMBER_R3________________     _______, _______, _______,TG(_FUN),_______
#else
#define __________________NUMBER_R3________________     _______, _______, _______, _______, _______
#endif


#define _________________FUNCTION_L1_______________     _______,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10
#define _________________FUNCTION_L2_______________     _______,  KC_F4 ,  KC_F5 ,  KC_F6 , KC_F11
#define _________________FUNCTION_L3_______________     _______,  KC_F1 ,  KC_F2 ,  KC_F3 , KC_F12

#define _________________FUNCTION_R1_______________     __________________NUMBER_R1________________
#define _________________FUNCTION_R2_______________     __________________NUMBER_R2________________
#define _________________FUNCTION_R3_______________     __________________NUMBER_R3________________

// clang-format on
