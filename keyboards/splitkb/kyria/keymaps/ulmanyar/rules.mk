OLED_ENABLE = yes
OLED_DRIVER = SSD1306   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
CAPS_WORD_ENABLE = yes     # Enable CapsWord to turn on Caps for current word only
TAP_DANCE_ENABLE = yes

SRC += oneshot.c
SRC += swapper.c
