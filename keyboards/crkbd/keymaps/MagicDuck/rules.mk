SPLIT_KEYBOARD = yes
BOOTLOADER = qmk-dfu  # Elite-C
OLED_DRIVER_ENABLE  = no
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = no
AUTO_SHIFT_ENABLE = no
COMBO_ENABLE = yes

CONSOLE_ENABLE    = no         # Console for debug(+400)
COMMAND_ENABLE    = no        # Commands for debug and configuration
AUDIO_ENABLE      = no
NKRO_ENABLE       = yes
BACKLIGHT_ENABLE  = no
SWAP_HANDS_ENABLE = no
SPACE_CADET_ENABLE = no
INDICATOR_LIGHTS  = no
RGBLIGHT_TWINKLE  = no
RGBLIGHT_STARTUP_ANIMATION = no

SRC += oneshot.c
SRC += swapper.c
