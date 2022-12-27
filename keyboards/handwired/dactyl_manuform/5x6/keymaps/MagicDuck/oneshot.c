#include "oneshot.h"

uint16_t immediateOneshotKey = 0;

void cancelMod(uint16_t mod) {
    unregister_mods(MOD_BIT(mod));
    immediateOneshotKey = 0;
#ifdef CONSOLE_ENABLE
    uprintf("canceled mod: %u\n", get_mods());
#endif
}
void activateMod(uint16_t mod) {
    register_mods(MOD_BIT(mod));
    immediateOneshotKey = 0;
#ifdef CONSOLE_ENABLE
    uprintf("activated mod %u\n", get_mods());
#endif
}

uint32_t cancelOneshotCb(uint32_t trigger_time, void *cb_arg) {
    oneshot_mod_state *mod_state = (oneshot_mod_state *)cb_arg;
    mod_state->state             = os_up_unqueued;
    cancelMod(mod_state->mod);
    return 0;
}

void update_oneshot(oneshot_mod_state *mod_state, uint16_t trigger, uint16_t keycode, keyrecord_t *record) {
    oneshot_state *state = &(mod_state->state);
    uint16_t       mod   = mod_state->mod;

    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                activateMod(mod);
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
                    cancelMod(mod);
                    break;
                default:
                    break;
            }
        }
    } else {
#ifdef CONSOLE_ENABLE
        uprintf("stephan: oneshot: key event, key: 0x%04X, pressed: %u, mod_state: %d, mods: %u\n", keycode, record->event.pressed, (int)*state, get_mods());
#endif
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                cancelMod(mod);
                return;
            }

            // Note: Even with this little guard in place, we still have issues when state is os_down_used, that is when the mod has not keyupped
            // In order to perfectly fix it, we would need to make it a dedicated onseshot only key, for example a shift that does only
            // oneshot, no hold, then cancel the mod on both os_down_unused and os_up_queued, as well as clear any layers so we don't end up
            // typing symbols
            if (!is_oneshot_ignored_key(keycode) && *state == os_up_queued) {
                if (immediateOneshotKey == 0) {
                    immediateOneshotKey = keycode;
                } else if (keycode == immediateOneshotKey) {
                    // do nothing
                } else {
                    // 2 or more keydowns in a row, happens with fast typing
                    // del_mods(MOD_BIT(mod));
                    cancelMod(mod);
                }
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
                        cancelMod(mod);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
