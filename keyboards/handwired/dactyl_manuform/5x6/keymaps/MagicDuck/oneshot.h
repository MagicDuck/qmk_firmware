#pragma once

#include QMK_KEYBOARD_H

// Represents the four states a oneshot key can be in
typedef enum {
    os_up_unqueued = 1,
    os_up_queued,
    os_down_unused,
    os_down_used,
} oneshot_state;

typedef struct {
    oneshot_state state;
    uint16_t      mod;
} oneshot_mod_state;

// Custom oneshot mod implementation that doesn't rely on timers. If a mod is
// used while it is held it will be unregistered on keyup as normal, otherwise
// it will be queued and only released after the next non-mod keyup.
void update_oneshot(oneshot_mod_state *mod_state, uint16_t trigger, uint16_t keycode, keyrecord_t *record);

// To be implemented by the consumer. Defines keys to cancel oneshot mods.
bool is_oneshot_cancel_key(uint16_t keycode);

// To be implemented by the consumer. Defines keys to ignore when determining
// whether a oneshot mod has been used. Setting this to modifiers and layer
// change keys allows stacking multiple oneshot modifiers, and carrying them
// between layers.
bool is_oneshot_ignored_key(uint16_t keycode);

// To be implemented by the consumer. Event handlers
void on_before_oneshot_mod_activate(oneshot_mod_state *mod_state, uint16_t keycode, keyrecord_t *record);
void on_before_oneshot_mod_cancel(oneshot_mod_state *mod_state, uint16_t keycode, keyrecord_t *record);
void on_before_oneshot_deferred_mod_cancel(oneshot_mod_state *mod_state);
