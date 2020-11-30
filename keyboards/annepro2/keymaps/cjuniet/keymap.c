#include QMK_KEYBOARD_H
#include "annepro2.h"

enum anne_pro_layers {
    _BASE_LAYER = 0,
    _SUPER_LAYER,
    _HYPER_LAYER,
};

enum tap_steps { SINGLE_TAP = 1, SINGLE_HOLD, DOUBLE_TAP };

enum tap_dances {
    TD_HYPER,
};

static uint8_t tap_state;
uint8_t        cur_dance(qk_tap_dance_state_t *state);
void           dance_finished(qk_tap_dance_state_t *state, void *user_data);
void           dance_reset(qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_HYPER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_finished, dance_reset),
};

// clang-format off
/*
* Layer _BASE_LAYER
* ,-----------------------------------------------------------------------------------------.
* | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
* |-----------------------------------------------------------------------------------------+
* | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
* |-----------------------------------------------------------------------------------------+
* | Ctrl    |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
* |-----------------------------------------------------------------------------------------+
* | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
* |-----------------------------------------------------------------------------------------+
* | Leader|  Alt  |  Gui  |               space             | Super |  Gui  |  Alt  | Ctrl  |
* \-----------------------------------------------------------------------------------------/
*/
const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE_LAYER] = KEYMAP( /* Base */
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    LT(_SUPER_LAYER,KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    TD(TD_HYPER), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
    KC_LEAD, KC_LALT, KC_LGUI, KC_SPC, MO(_SUPER_LAYER), KC_RGUI, KC_RALT, KC_RCTL
  ),

/*
* Layer _SUPER_LAYER
* ,-----------------------------------------------------------------------------------------.
* |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  DELETE   |
* |-----------------------------------------------------------------------------------------+
* | Tab    |HOME | UP  | END |PGUP |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   ~    |
* |-----------------------------------------------------------------------------------------+
* | Hyper   |LEFT |DOWN |RIGHT|PGDN |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
* |-----------------------------------------------------------------------------------------+
* | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
* |-----------------------------------------------------------------------------------------+
* | Ctrl  |  Alt  |  Gui  |               space             | Super |  Gui  |  Alt  | Ctrl  |
* \-----------------------------------------------------------------------------------------/
*
*/
  [_SUPER_LAYER] = KEYMAP(
    KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
    KC_TAB, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_HOME, KC_END, KC_TILD,
    MO(_HYPER_LAYER), KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

/*
* Layer _HYPER_LAYER
* ,-----------------------------------------------------------------------------------------.
* |  `  | BT1 | BT2 | BT3 | BT4 |  F5 |  F6 |  F7 |  F8 |LEDON|LEDOF| F11 | F12 |  DELETE   |
* |-----------------------------------------------------------------------------------------+
* | Tab    | MS1 | MSU | MS2 | MWU |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   ~    |
* |-----------------------------------------------------------------------------------------+
* | Hyper   | MSL | MSD | MSR | MHD |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
* |-----------------------------------------------------------------------------------------+
* | Shift      |V-DWN|V-UP |MUTE |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Up          |
* |-----------------------------------------------------------------------------------------+
* | Ctrl  |  Alt  |  Gui  |               space             | Super |  Left |  Down | Right |
* \-----------------------------------------------------------------------------------------/
*
*/
  [_HYPER_LAYER] = KEYMAP(
    KC_TRNS, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_AP_LED_ON, KC_AP_LED_OFF, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_HOME, KC_END, KC_TRNS,
    KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS,
    KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_DEL, KC_UP,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT
  ),
};
// clang-format on

const uint16_t keymaps_size = sizeof(keymaps);

void matrix_init_user(void) {}

LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

	// vi
        SEQ_ONE_KEY(KC_Z) { SEND_STRING(SS_TAP(X_ESC) SS_LSFT("zz")); }
        SEQ_ONE_KEY(KC_X) { SEND_STRING(SS_TAP(X_ESC) SS_LSFT("zq")); }
        SEQ_ONE_KEY(KC_C) { SEND_STRING("\"+y"); }
        SEQ_ONE_KEY(KC_V) { SEND_STRING("\"+p"); }

	// kitty
        SEQ_ONE_KEY(KC_A) { tap_code16(LCTL(LSFT(KC_LEFT))); }
        SEQ_ONE_KEY(KC_D) { tap_code16(LCTL(LSFT(KC_RIGHT))); }
    }
}

layer_state_t layer_state_set_user(layer_state_t layer) { return layer; }

uint8_t cur_dance(qk_tap_dance_state_t *state) {
    switch (state->count) {
        case 1:
            return (!state->pressed ? SINGLE_TAP : SINGLE_HOLD);
        case 2:
            return DOUBLE_TAP;
        default:
            return 0;
    }
}

void dance_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state = cur_dance(state);
    switch (tap_state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            register_code16(KC_LCTRL);
            break;
        case DOUBLE_TAP:
            if (layer_state_is(_HYPER_LAYER)) {
                layer_off(_HYPER_LAYER);
            } else {
                layer_on(_HYPER_LAYER);
            }
            break;
    }
}

void dance_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (tap_state == SINGLE_HOLD) {
        unregister_code16(KC_LCTRL);
    }
    tap_state = 0;
}
