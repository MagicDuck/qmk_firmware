#include QMK_KEYBOARD_H
#include "keymap_combo.h"
#include "oneshot.h"
#include "swapper.h"
#include "repeat.h"

enum layers {
    BASE_LAYER,
    SYM_LAYER,
    NAV_LAYER,
    NUM_LAYER,
};

enum keycodes {
    // Custom oneshot mod implementation.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN, // Switch to next window         (cmd-tab)
    SW_TAB, // Switch to next tab            (ctrl-tab)
    REPEAT,
    CODE_BLK
};

#define OSM_HYPR OSM(MOD_HYPR)
#define OSL_LSFT OSM(MOD_LSFT)
#define OS_LGUI OSM(MOD_LGUI)
// #define OS_LCTL OSM(MOD_LCTL)
// #define OS_LALT OSM(MOD_LALT)

// #define OSL_SYM OSL(SYM_LAYER)
// #define SYM MO(SYM_LAYER)
#define SYM OSL(SYM_LAYER)
// #define NAV MO(NAV_LAYER)
#define NAV OSL(NAV_LAYER)
#define NAVH MO(NAV_LAYER)
// #define OSL_NAV OSL(NAV_LAYER)
#define OSL_NUM OSL(NUM_LAYER)
#define OSM_SFT OSM(MOD_LSFT)

// #define SFT_A LSFT_T(KC_A)
// #define SFT_SCLN LSFT_T(KC_SCLN)
// #define SFT_V LSFT_T(KC_V)
// #define SFT_M LSFT_T(KC_M)

#define SEL_ALL LCMD(KC_A)
#define COPY LCMD(KC_C)
#define PASTE LCMD(KC_V)
#define CUT LCMD(KC_X)
#define UNDO LCMD(KC_Z)
#define RELOAD LCMD(KC_R)
#define FIND LCMD(KC_F)
#define DEL_WD LALT(KC_DEL)
#define BSPC_WD LALT(KC_BSPC)
#define DEL_LN LCMD(KC_DEL)
#define BSPC_LN LCMD(KC_BSPC)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE_LAYER] = LAYOUT_5x6(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_PSCR,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼                          ┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴                          ┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                      KC_LEFT, KC_RIGHT,                                                               KC_UP,   KC_DOWN,
                  // └────────┴────────┘                                                              └────────┴────────┘
                                      //┌────────┬────────┐                          ┌────────┬────────┐ 
                                         KC_LSFT, _______,                            _______,  KC_SPC,
                                      //├────────┼────────┼                          ├────────┼────────┼
                                         KC_LCTL, NAV,                                SYM,     KC_LCTL,
                                      //├────────┼────────┼                          ├────────┼────────┼
                                         KC_LGUI, KC_HYPR,                            KC_ENT, KC_LGUI
                                         /* KC_LGUI, KC_HYPR,                            KC_HYPR, KC_LGUI */
                                      //└────────┴────────┘                          └────────┴────────┘
                                      // //┌────────┬────────┐                          ┌────────┬────────┐ 
                                      //    OSL_LSFT, _______,                            _______,  KC_SPC,
                                      // //├────────┼────────┼                          ├────────┼────────┼
                                      //    KC_LCTL, OSL_NAV,                           OSL_SYM, KC_LCTL,
                                      // //├────────┼────────┼                          ├────────┼────────┼
                                      //    KC_LGUI, OSL_HYPR,                           KC_LALT, KC_LGUI
                                      // //└────────┴────────┘                          └────────┴────────┘
  ),

  [SYM_LAYER] = LAYOUT_5x6(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, KC_LBRC, KC_RBRC, _______,                            _______, _______, _______, _______, _______, QK_BOOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_PERC, KC_GRV,  KC_EQL,  KC_AMPR, KC_PIPE,                            KC_DLR ,  KC_TILD, KC_ASTR, KC_PLUS, KC_HASH, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_DQT,  KC_QUOT, KC_LPRN, KC_RPRN, KC_MINS,                            KC_AT,   OS_CMD,  OS_CTRL, OS_ALT,  OS_SHFT, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼                          ┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_BSLS, KC_EXLM, KC_LCBR, KC_RCBR, KC_UNDS,                             KC_CIRC, KC_SCLN, KC_LT,   KC_GT,   KC_QUES, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬                 ┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                      _______, _______,                                                                _______, _______,
                  // └────────┴────────┘                                                              └────────┴────────┘
                                      //┌────────┬────────┐                          ┌────────┬────────┐ 
                                         KC_TAB,  _______,                            _______, _______,
                                      //├────────┼────────┼                          ├────────┼────────┼
                                         _______, NAV,                               _______, _______,
                                      //├────────┼────────┼                          ├────────┼────────┼
                                         _______, _______,                            _______, _______
                                      //└────────┴────────┘                          └────────┴────────┘
  ),
  
  [NAV_LAYER] = LAYOUT_5x6(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     QK_BOOT,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                             KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, OSM_HYPR, RELOAD,  REPEAT,                           KC_HOME,  KC_PGDN, KC_PGUP, BSPC_LN, DEL_LN,  KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, OS_SHFT, OS_ALT,  OS_CTRL, OS_CMD,  SW_WIN,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  KC_END,  _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼                          ┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, UNDO,    CUT,     COPY,    PASTE,   SW_TAB,                            BSPC_WD, KC_BSPC, KC_DEL,  DEL_WD,   CODE_BLK, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬                 ┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                      _______, _______,                                                                _______, _______,
                  // └────────┴────────┘                                                              └────────┴────────┘
                                      //┌────────┬────────┐                          ┌────────┬────────┐ 
                                         _______, _______,                            _______, _______,
                                      //├────────┼────────┼                          ├────────┼────────┼
                                         /* _______, _______,                            KC_ENT,  _______, */
                                         _______, _______,                            _______,  _______,
                                      //├────────┼────────┼                          ├────────┼────────┼
                                         _______, _______,                            _______, _______
                                      //└────────┴────────┘                          └────────┴────────┘
  )
  //
  // [NUM_LAYER] = LAYOUT(
  // //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
  //    _______, _______, KC_1,    KC_2,    KC_3,    _______,                            _______, _______, _______, _______, _______, _______,
  // //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //    _______, KC_0,    KC_4,    KC_5,    KC_6,    KC_DOT,                             _______, _______, _______, _______, _______, _______,
  // //├────────┼────────┼────────┼────────┼────────┼────────┼                          ┼────────┼────────┼────────┼────────┼────────┼────────┤
  //    _______, _______, KC_7,    KC_8,    KC_9,    _______,                            _______, _______, _______, _______, _______, _______,
  // //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬                 ┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
  //                                   _______, _______, _______,                   _______, _______, _______
  //                               // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  // ),

};
// clang-format on

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        // case OSL_NAV:
        case KC_HYPR:
        case OSM_HYPR:
        case KC_LGUI:
        case KC_LCTL:
        case OSL_NUM:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case NAV:
        case SYM:
        case OSL_NUM:
        case KC_LSFT:
        case OS_SHFT:
        case OS_CTRL:
        case OS_ALT:
        case OS_CMD:
            return true;
        default:
            return false;
    }
}

void process_snippets(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case CODE_BLK:
                SEND_STRING("```\n\n```" SS_TAP(X_UP));
                break;
        }
    }
}

bool sw_win_active = false;
bool sw_tab_active = false;

oneshot_mod_state os_shft_state = {.mod = KC_LSFT, .state = os_up_unqueued};
oneshot_mod_state os_ctrl_state = {.mod = KC_LCTL, .state = os_up_unqueued};
oneshot_mod_state os_alt_state  = {.mod = KC_LALT, .state = os_up_unqueued};
oneshot_mod_state os_cmd_state  = {.mod = KC_LCMD, .state = os_up_unqueued};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // window swapper
    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, keycode, record);
    update_swapper(&sw_tab_active, KC_LCTL, KC_TAB, SW_TAB, keycode, record);

    // oneshot mods
    update_oneshot(&os_shft_state, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, OS_ALT, keycode, record);
    update_oneshot(&os_cmd_state, OS_CMD, keycode, record);

    // repeat last key
    process_repeat_key(REPEAT, keycode, record);

    // snippets
    process_snippets(keycode, record);

    return true;
}
