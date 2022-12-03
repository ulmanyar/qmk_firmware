/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
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

#pragma once

#ifdef TAP_DANCE_ENABLE
#    define TAPPING_TERM 125
#    define TAPPING_TERM_PER_KEY
#endif

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_SLEEP           # Turn RGB underglow off when power off
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
#    define RGBLIGHT_LIMIT_VAL 150
#endif

// Lets you roll mod-tap keys
// #define IGNORE_MOD_TAP_INTERRUPT
#define RETRO_TAPPING_PER_KEY

// EC11K encoders have a different resolution than other EC11 encoders.
// When using the default resolution of 4, if you notice your encoder skipping
// every other tick, lower the resolution to 2.
#define ENCODER_RESOLUTION 2

#define DISPLAY_KYRIA_LOGO

#define ACCSCROLL_MAX_STEP 18
#define ACCSCROLL_STEP_SIZE 3
#define ACCSCROLL_REPEAT_INTERVAL 75
