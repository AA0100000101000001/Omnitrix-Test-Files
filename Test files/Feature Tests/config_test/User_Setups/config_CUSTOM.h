
/*	Edit this file to make new configuration files for other boards */

//Uncomment for CST816S touch driver and GC9A01 lcd display
//#define ESP32_S3_TOUCH_LCD_1_28
//Uncomment for no touch GC9A01 display
//#define ESP32_S2_PINOUT //or
//#define ESP32_S3_PINOUT

//Define input pins for pop up buttons if enabled
#define CONFIG_START_BUTTON_PIN 	0 //write pin
#define CONFIG_SELECT_BUTTON_PIN 	0 //write pin

//ROTARY. Define rotary encoder input pins if enabled
#define CONFIG_RIGHT_BUTTON_PIN		0 //write pin
#define CONFIG_LEFT_BUTTON_PIN		0 //write pin

//SOUND 1. Dfplayer Pro pins if sound and dflpayer are enabled
#define CONFIG_RXD1 0 //write pin
#define CONFIG_TXD1 0 //write pin

//SOUND 2. Buzzer pins if sound and buzzer are enabled
#define CONFIG_BUZZER 0 //write pin


//LED 1. Define RGB LED pins if enabled
#define CONFIG_RGB_LED_R 0 //write pin
#define CONFIG_RGB_LED_G 0 //write pin
#define CONFIG_RGB_LED_B 0 //write pin

//LED 2. Define Neopixel ring LEDs if enabled
#define CONFIG_DI 0 //write pin

//LED 3. Define IR controlled LEDs if enabled
#define CONFIG_IR_TRANSMITTER 0 //write pin






//Uncomment for use of buttons for the pop up mechanism
#define POP_UP_BUTTONS_ENABLED

//Define input pins
#define CONFIG_START_BUTTON_PIN 	//write pin
#define CONFIG_SELECT_BUTTON_PIN 	//write pin

//Use one of these options for rotary encoder
//1. Uncomment for use of micro switches for encoder
#define MICRO_SWITCHES_ROTARY_ENCODER_ENABLED
//2. Uncomment for use of magnetic encoder
#define ROTARY_ENCODER_ENABLED
//3. Uncomment for use of magnetic encoder
#define MAGNETIC_ROTARY_ENCODER_ENABLED

//Define rotary encoder input pins
#define CONFIG_RIGHT_BUTTON_PIN		//write pin
#define CONFIG_LEFT_BUTTON_PIN		//write pin


//Uncomment for sound
#define SOUND_ENABLED

//Use one of these options for sound
//1. Uncomment for use of Dfplayer Pro for sound
#define SOUND_DFPLAYER_PRO_ENABLED

//Dfplayer Pro pins
#define CONFIG_RXD1 //write pin
#define CONFIG_TXD1 //write pin

//2. Uncomment for use of buzzer for sound
#define SOUND_BUZZER_ENABLED

//Buzzer pins
#define CONFIG_BUZZER //write pin

//Uncomment for LEDs
#define LEDS_ENABLED

//Uncomment for RGB LEDs
#define RGB_LEDS_ENABLED

//1. Define RGB LED pins
#define CONFIG_RGB_LED_R	//write pin
#define CONFIG_RGB_LED_G	//write pin
#define CONFIG_RGB_LED_B	//write pin

//2. Uncomment for Neopixel ring LEDs
#define NEOPIXEL_RING_LEDS_ENABLED

#define CONFIG_DI //write pin

//3. Uncomment for IR controlled LEDs
#define IR_CONTROLLED_LEDS_ENABLED

#define CONFIG_IR_TRANSMITTER //write pin



