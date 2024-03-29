# How to use 
This is a test for configuring pins using #ifdef. User_Setups folder contains various configurations for some boards to use. File config_DEFAULT has all boards uncommented and all inputs and outputs enabled. Edit config_DEFAULT to create your own configuration or uncomment your preferred configuration.  
# Tested with 
* ESP32-S2-DEV  
* ESP32-S3 TOUCH LCD 1.28
# Configuration Variables  
## Boards Supported 
* ESP32_S2_DEV
* ESP32_S3_TOUCH_LCD_1_28
## Features  
* POP_UP_BUTTONS_ENABLED
* MICRO_SWITCHES_ROTARY_ENCODER_ENABLED or MAGNETIC_ROTARY_ENCODER_ENABLED
* SOUND_ENABLED (SOUND_DFPLAYER_PRO_ENABLED or SOUND_BUZZER_ENABLED)
* RGB_LEDS_ENABLED
* START_ANIMATION_WITH_IMAGES or START_ANIMATION_WITHOUT_IMAGES
## Inputs 
* START_BUTTON_PIN
* SELECT_BUTTON_PIN
* RIGHT_BUTTON_PIN
* LEFT_BUTTON_PIN
## Outputs 
* For sound: RXD1, TXD1 or BUZZER
* RGB_LED_R
* RGB_LED_G
* RGB_LED_B
# Boolean Expressions For Defines
Using XOR so only one type of animation, sound, LEDs can be allowed to be enabled
### For Two Inputs
(A NOT B) + (NOT A B) returns true if only one of A, B is true  
(A == B returns true if A and B are both false or true)
### For Three Inputs
(NOT A NOT B C) + (NOT A B NOT C) + (A NOT B NOT C) returns true if only one of A, B, C is true