// COMBOS
// The need for this file is partially as a workaround to this:
// https://github.com/qmk/qmk_firmware/issues/21137
// https://discord.com/channels/440868230475677696/869812721552601088/1114067579166806086

#ifdef COMBO_ENABLE
enum combos {
  TN_ESC,
  AR_ESC,
  ST_TAB,
  IO_ENTER,
  NE_BSPC,
  NEI_C_BSPC,
  LUY_A_BSPC,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM tn_combo[] = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM ar_combo[] = {KC_A, KC_R, COMBO_END};
const uint16_t PROGMEM st_combo[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM ne_combo[] = {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM nei_combo[] = {KC_N, KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM luy_combo[] = {KC_L, KC_U, KC_Y, COMBO_END};

combo_t key_combos[] = {
  [TN_ESC] = COMBO(tn_combo, KC_ESC),
  [AR_ESC] = COMBO(ar_combo, KC_ESC),
  [ST_TAB] = COMBO(st_combo, KC_TAB),
  [IO_ENTER] = COMBO(io_combo, KC_ENT),
  [NE_BSPC] = COMBO(ne_combo, KC_BSPC),
  [NEI_C_BSPC] = COMBO(nei_combo, C(KC_BSPC)),
  [LUY_A_BSPC] = COMBO(luy_combo, A(KC_BSPC)),
};

#endif // COMBO_ENABLE
