
/*	Edit this file to make new configuration files for other boards */

//Uncomment for CST816S touch driver and GC9A01 lcd display
//#define ESP32_S3_TOUCH_LCD_1_28
//Uncomment for no touch GC9A01 display
//#define ESP32_S2_PINOUT //or
//#define ESP32_S3_PINOUT


//Uncomment for use of buttons for the pop up mechanism
#define POP_UP_BUTTONS_ENABLED

//Define input pins
#define CONFIG_START_BUTTON_PIN 	//write pin
#define CONFIG_SELECT_BUTTON_PIN 	//write pin

//Use one of these options for rotary encoder
//Uncomment for use of micro switches for encoder
#define MICRO_SWITCHES_ROTARY_ENCODER_ENABLED
//Uncomment for use of magnetic encoder
#define MAGNETIC_ROTARY_ENCODER_ENABLED

//Define rotary encoder input pins
#define CONFIG_RIGHT_BUTTON_PIN		//write pin
#define CONFIG_LEFT_BUTTON_PIN		//write pin


//Uncomment for sound
#define SOUND_ENABLED

//Use one of these options for sound
//Uncomment for use of Dfplayer Pro for sound
#define SOUND_DFPLAYER_PRO_ENABLED

//Dfplayer Pro pins
#define CONFIG_RXD1 //write pin
#define CONFIG_TXD1 //write pin

//Uncomment for use of buzzer for sound
#define SOUND_BUZZER_ENABLED

//Buzzer pins
#define CONFIG_BUZZER //write pin

//Uncomment for RGB LEDS
#define RGB_LEDS_ENABLED

//Define RGB LED pins
#define CONFIG_RGB_LED_R	//write pin
#define CONFIG_RGB_LED_G	//write pin
#define CONFIG_RGB_LED_B	//write pin



