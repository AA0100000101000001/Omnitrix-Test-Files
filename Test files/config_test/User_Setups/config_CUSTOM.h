
/*	Edit this file to make new configuration files for other boards
*/

//Uncomment for CST816S touch driver and GC9A01 lcd display
//#define ESP32_S3_TOUCH_LCD_1_28
//Uncomment for no touch GC9A01 display
//#define ESP32_S2_PINOUT

//Uncomment for buttons
#define BUTTONS_ENABLED

//Define button pins
#define CONFIG_START_BUTTON_PIN 	START_BUTTON_PIN_SELECTION //write value
#define CONFIG_RIGHT_BUTTON_PIN		RIGHT_BUTTON_PIN_SELECTION //write value
#define CONFIG_LEFT_BUTTON_PIN		LEFT_BUTTON_PIN_SELECTION //write value
#define CONFIG_SELECT_BUTTON_PIN 	SELECT_BUTTON_PIN_SELECTION //write value


//Uncomment for sound
#define SOUND_ENABLED


//Uncomment for RGB LEDS
#define RGB_LEDS_ENABLED

//Define RGB LED pins
#define CONFIG_RGB_LED_R	RGB_LED_R_SELECTION //write value
#define CONFIG_RGB_LED_G	RGB_LED_G_SELECTION //write value
#define CONFIG_RGB_LED_B	RGB_LED_B_SELECTION //write value



