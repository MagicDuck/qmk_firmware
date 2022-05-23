#include "oneshot.h"

uint32_t cancelOneshotCb(uint32_t trigger_time, void *cb_arg) {
  oneshot_mod_state *mod_state = (oneshot_mod_state *) cb_arg; 
  mod_state->state = os_up_unqueued;
  unregister_code(mod_state->mod);
  return 0;
}

void update_oneshot(
    oneshot_mod_state *mod_state,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    oneshot_state *state = &(mod_state->state);
    uint16_t mod = mod_state->mod;

    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                register_code(mod);
            }
            *state = os_down_unused;
        } else {
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                *state = os_up_queued;
                defer_exec(ONESHOT_TIMEOUT, cancelOneshotCb, mod_state);
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                *state = os_up_unqueued;
                unregister_code(mod);
                break;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                unregister_code(mod);
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_down_unused:
                    *state = os_down_used;
                    break;
                case os_up_queued:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    break;
                default:
                    break;
                }
            }
        }
    }
}
