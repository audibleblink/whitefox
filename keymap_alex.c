#include "keymap_common.h"
#include "led_controller.h"

/* Layer 0: Default Layer
 * ,---------------------------------------------------------------.
 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| Backsp| ` |
 * |---------------------------------------------------------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   \ |Del|
 * |---------------------------------------------------------------|
 * |CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  Enter |PgU|
 * |---------------------------------------------------------------|
 * |Shift   | Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| Shift |Up |PgD|
 * |---------------------------------------------------------------|
 * |Ctrl|Gui |Alt |         Space       |Alt |Gui |Ctrl|Lef|Dow|Rig|
 * `---------------------------------------------------------------'
 */

const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = KEYMAP( \
      GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, NO, BSPC, FN5, \
      TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     DEL, \
      FN0,  A,   S,   D, FN3,   G,   H,   J,   K,   L,   SCLN,QUOT,NUHS,ENT,     FN4, \
      LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,     UP,  PGDN,\
      FN2,LALT,LGUI,               SPC,           RALT,FN1, RCTL,      LEFT,DOWN,RGHT \
      ),
  [1] = KEYMAP( \
      TRNS,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,TRNS,MUTE,\
      TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS,TRNS,     TRNS,\
      TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     VOLU,\
      TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     PGUP,VOLD,\
      TRNS,TRNS,TRNS,               TRNS,          TRNS,TRNS,TRNS,     HOME,PGDN,END  \
      ),
  [2] = KEYMAP( \
      TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,\
      TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,   7,   8,   9,TRNS,TRNS,TRNS,TRNS,     TRNS,\
      TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,   4,   5,   6,TRNS,TRNS,TRNS,TRNS,     TRNS,\
      TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,   1,   2,   3, DOT,TRNS,     TRNS,TRNS,\
      TRNS,TRNS,TRNS,               0,            TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS  \
      ),
  /* Arrow Layer - S key */
  [3] = KEYMAP( \
      TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,\
      TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,\
      TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,LEFT,DOWN,  UP,RGHT,TRNS,TRNS,TRNS,TRNS,     TRNS,\
      TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,\
      TRNS,TRNS,TRNS,               TRNS,          TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS  \
      ),
};

/* Give numbers some descriptive names */
#define ACTION_LEDS_ALL 1
#define ACTION_LEDS_GAME 2

const action_t fn_actions[] = {
  [0] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_ESCAPE),
  [1] = ACTION_LAYER_MOMENTARY(1),
  [2] = ACTION_LAYER_MOMENTARY(2),
  [3] = ACTION_LAYER_TAP_KEY(3, KC_F),
  [4] = ACTION_FUNCTION(ACTION_LEDS_ALL),
  [5] = ACTION_FUNCTION(ACTION_LEDS_GAME),
};


/* Custom Functions */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  (void)opt;
  switch(id) {
    case ACTION_LEDS_ALL:
      if(record->event.pressed) {
        // signal the LED controller thread
        chMBPost(&led_mailbox, LED_MSG_GAME_TOGGLE, TIME_IMMEDIATE);
      }
      break;
    case ACTION_LEDS_GAME:
      if(record->event.pressed) {
        // signal the LED controller thread
        chMBPost(&led_mailbox, LED_MSG_ALL_TOGGLE, TIME_IMMEDIATE);
      }
      break;
  }
}
