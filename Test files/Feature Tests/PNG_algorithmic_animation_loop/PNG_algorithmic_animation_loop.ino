

#include <TFT_eSPI.h>
#include <PNGdec.h>
#include <SPI.h>

PNG png;  // PNG decoder instance
TFT_eSPI tft = TFT_eSPI();

void show_symbols();
void show_alien();
int png_draw(PNGDRAW *pDraw);

#define MAX_IMAGE_WDITH 240  // Set rendering line buffer lengths for image

//CPU FREQUENCY
#define DEFAULT_CPU_FREQ 80
//Allow cpu frequency to change for better FPS
//#define ALLOW_CPU_FREQ_CHANGES
//#define MAX_CPU_FREQ 80
//#define MAX_CPU_FREQ 160
//#define MAX_CPU_FREQ 240

//Animation timing with certain frequencies
#if defined ALLOW_CPU_FREQ_CHANGES
#if MAX_CPU_FREQ == 80
#define FRAME_RATE 53 //For freq of 80
#elif MAX_CPU_FREQ == 160
#define FRAME_RATE 31 //For freq of 160
#elif MAX_CPU_FREQ == 240
#define FRAME_RATE 24 //For freq of 240
#endif
#else
#define FRAME_RATE 53 //For freq of 80
#endif

//SERIAL OUTPUT
//Basic debugging info
//#define ENABLE_MEMORY_INFO
#define ENABLE_ANIM_INFO
//#define ENABLE_VERBOSE_ANIM_INFO


//1. Start animation with images
#define START_ANIMATION_WITH_IMAGES
//2. Hard coded start animation
//#define START_ANIMATION_WITHOUT_IMAGES //Not finished

//Start animation with images
#if defined START_ANIMATION_WITH_IMAGES
#include "omnitrix_anim.h"
#endif

#define OMNITRIX_GREEN 0xA707
#define OMNITRIX_RED 0xC000
#define OMNITRIX_GRAY 0xAD55

static bool is_animating = false;
uint32_t g_anim_start;    //Timer that helps with animation
uint8_t g_current_frame; //Frame iterator (<= 255 total frames)

void setup() {
  
  Serial.begin(115200);
  setCpuFrequencyMhz(DEFAULT_CPU_FREQ);

  tft.begin();
  delay(400);
  tft.fillScreen(OMNITRIX_GREEN);
  show_symbols();
  delay(1000);

  start_animation();

}

void loop() {
  
  //Animation for going to select alien mode is done
  if(is_animating) {

    // Animation time is done
    if (show_animation()) {

#if defined ENABLE_ANIM_INFO
      Serial.println("Start animation is done");
#endif

      is_animating = false;
      finish_animation();
    }
    //Do not allow other inputs to be read
    return;
  }

  delay(400);
  tft.fillScreen(OMNITRIX_GREEN);
  show_symbols();
  delay(1000);
  start_animation();
}

void start_animation() {

  //reset_timer(); // For the delay of the animation
  g_anim_start = millis(); //get time of animation begin
  is_animating = true;

#if defined ALLOW_CPU_FREQ_CHANGES
  //Change cpu frequency to the faster allowed one for faster animation
  setCpuFrequencyMhz(MAX_CPU_FREQ); //Change cpu frequency to the faster allowed one 
#endif
  g_current_frame = 0; //Set start frame
  //Set debugging animation variables
#if defined ENABLE_VERBOSE_ANIM_INFO
  end_animation_time;
  avrg_frame_time = 0;
  avrg_frame_decod_time = 0;
#endif

}

void finish_animation() {

#if defined ALLOW_CPU_FREQ_CHANGES
  //Change cpu frequency to the default one for battery
  setCpuFrequencyMhz(DEFAULT_CPU_FREQ); //Change cpu frequency to the faster allowed one 
#endif

}
