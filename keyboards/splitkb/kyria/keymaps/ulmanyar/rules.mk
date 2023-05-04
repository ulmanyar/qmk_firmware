OLED_ENABLE = yes
OLED_DRIVER = SSD1306   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = no      # Enable keyboard RGB underglow, approximately 4865 bytes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes

SRC += ulmanyar.c
SRC += oneshot.c
SRC += swapper.c
