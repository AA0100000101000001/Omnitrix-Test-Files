# How to use 
This is a test for configuring pins using #ifdef. User_Setups folder contains various configurations for some boards to use. File config_DEFAULT has all boards uncommented and all inputs and outputs enabled. Edit config_DEFAULT to create your own configuration or uncomment your preferred configuration.  
# Tested with 
* ESP32-S2-DEV  
* ESP32-S3 TOUCH LCD 1.28
# Configuration Variables  
## Boards Supported 
* ESP32_S3_TOUCH_LCD_1_28
* ESP32_S2_DEV
## Features  
* BUTTONS_ENABLED
* SOUND_ENABLED
* RGB_LEDS_ENABLED
## Input Pins 
* START_BUTTON_PIN
* RIGHT_BUTTON_PIN
* LEFT_BUTTON_PIN
* SELECT_BUTTON_PIN
## Output Pins
* RGB_LED_R
* RGB_LED_G
* RGB_LED_B