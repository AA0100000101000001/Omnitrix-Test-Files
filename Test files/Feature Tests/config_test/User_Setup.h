
//Pin configuration
//Edit User_Setups/config_DEFAULT to create your own configuration or uncomment your preferred configuration
#include "User_Setups/config_ESP32_S2_PINOUT.h"
//#include "User_Setups/config_ESP32_S3_PINOUT.h"
//#include "User_Setups/config_ESP32_S3_TOUCH_LCD_1_28.h"


//Software Settings

//Choose only one type of animation
//Start animation with images
#define START_ANIMATION_WITH_IMAGES //Has memory leaks
//Hard coded start animation
//#define START_ANIMATION_WITHOUT_IMAGES //Not finished

//-------------------------------------------------------
//----------DON'T EDIT THIS------------------------------
//-------------------------------------------------------


//Define button pins for the pop up mechanism
#if defined POP_UP_BUTTONS_ENABLED

	#define START_BUTTON_PIN 	CONFIG_START_BUTTON_PIN //Start button
	#define SELECT_BUTTON_PIN	CONFIG_SELECT_BUTTON_PIN //Select button

#endif

//Define input pins for the rotary encoder
#if defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED == defined MAGNETIC_ROTARY_ENCODER_ENABLED //XOR
#error "You must use at least only one option for the rotary encoder"
#else
	
	#define RIGHT_BUTTON_PIN	CONFIG_RIGHT_BUTTON_PIN //Right button
	#define LEFT_BUTTON_PIN		CONFIG_LEFT_BUTTON_PIN //Left button
	
#endif

//Check if sound is enabled
#if defined SOUND_ENABLED
	
	//Check which sound is enabled
	#if defined SOUND_DFPLAYER_PRO_ENABLED == defined SOUND_BUZZER_ENABLED //XOR
	#error "You must use at least only one option for the sound"
	#else
		//Dfplayer pro sound
		#if defined SOUND_DFPLAYER_PRO_ENABLED
			#define RXD1 CONFIG_RXD1 //RX1
			#define TXD1 CONFIG_TXD1 //TX1
		//#endif
		
		//Buzzzer sound
		#elif defined SOUND_BUZZER_ENABLED
			#define BUZZER_PIN CONFIG_BUZZER //buzzer
		#endif
		
	#endif

#endif

//Define RGB LED pins
#if defined RGB_LEDS_ENABLED

	#define RGB_LED_R CONFIG_RGB_LED_R //Red
	#define RGB_LED_G CONFIG_RGB_LED_G //Green
	#define RGB_LED_B CONFIG_RGB_LED_B //Blue

#endif

//Check type of animation
#if defined START_ANIMATION_WITH_IMAGES == defined START_ANIMATION_WITHOUT_IMAGES //XOR
#error "You must use at least only one option for the start animation"
#endif

/* Failed LCD pin configuration
//Define Esp32-s2 development board pins
#if defined ESP32_S2_PINOUT
  #include "User_Setups/Setup303_ESP32S2_GC9A01.h"
#endif

//Define Esp32-s3 touch LCD pins
#if defined ESP32_S3_TOUCH_LCD_1_28
	//Using integrated Touch LCD with GC9A01/CST816S drivers
  #include "User_Setups/Setup302_ESP32S3_GC9A01_TOUCH.h"
#endif
*/

//-------------------------------------------------------
//----------DON'T EDIT THIS------------------------------
//-------------------------------------------------------