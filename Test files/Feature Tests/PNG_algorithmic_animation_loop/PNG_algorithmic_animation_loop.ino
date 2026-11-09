

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
#define ENABLE_VERBOSE_ANIM_INFO


//1. Start animation with images
//#define START_ANIMATION_WITH_IMAGES
//2. Hard coded start animation
#define START_ANIMATION_HARD_CODED

//Start animation with images
//#if defined START_ANIMATION_WITH_IMAGES
#include "omnitrix_anim.h"
//#endif

#if defined START_ANIMATION_HARD_CODED

//Animation configuration
#define TFT_WIDTH_USED 240 //default
#define TFT_HEIGHT_USED 240 //default

//-------Edit these----------------
#define ANIM_TRIANGLE_WIDTH 74 //default, must be lower than TFT_WIDTH_MIDDLE
#define ANIM_TRIANGLE_BASE_OFFSET -6 //default
#define ANIM_TRIANGLE_PIXELS_TRAVEL 215 //default, must be lower than TFT_WIDTH_USED and higher than TFT_WIDTH_MIDDLE+ANIM_TRIANGLE_WIDTH
#define BLACK_LINE_WIDTH 11 //default
//----------------------------------

//Automatically calculated animation values
#define TFT_WIDTH_MIDDLE (TFT_WIDTH_USED/2) //120 in default
#define TFT_HEIGHT_MIDDLE (TFT_HEIGHT_USED/2) //120 in default
// 80 in default
#define ANIM_TRIANGLE_START_LEFT_OFFSET (ANIM_TRIANGLE_WIDTH - ANIM_TRIANGLE_BASE_OFFSET)
// 320 in default
#define ANIM_TRIANGLE_START_RIGHT_OFFSET (ANIM_TRIANGLE_WIDTH - ANIM_TRIANGLE_BASE_OFFSET + TFT_WIDTH_USED)
// 8 in default
#define ANIM_END_WIDTH_OFFSET 2*(ANIM_TRIANGLE_PIXELS_TRAVEL-BLACK_LINE_WIDTH-ANIM_TRIANGLE_START_LEFT_OFFSET-TFT_WIDTH_MIDDLE)
//#define ANIM_SELECT_SYM_END (TFT_WIDTH_USED- ANIM_TRIANGLE_PIXELS_TRAVEL-BLACK_LINE_WIDTH-ANIM_TRIANGLE_WIDTH)

//Check for animation configuration errors
#if ANIM_TRIANGLE_WIDTH >= TFT_WIDTH_MIDDLE
#error "ANIM_TRIANGLE_WIDTH must be lower than TFT_WIDTH_MIDDLE"
#elif ANIM_TRIANGLE_PIXELS_TRAVEL < (TFT_WIDTH_MIDDLE+ANIM_TRIANGLE_WIDTH)
#error "ANIM_TRIANGLE_PIXELS_TRAVEL must higher than TFT_WIDTH_MIDDLE+ANIM_TRIANGLE_WIDTH"
#elif ANIM_TRIANGLE_PIXELS_TRAVEL >= TFT_WIDTH_USED
#error "ANIM_TRIANGLE_PIXELS_TRAVEL must be lower than half of tft width"
#elif ANIM_TRIANGLE_START_LEFT_OFFSET >= TFT_WIDTH_MIDDLE
#error "ANIM_TRIANGLE_WIDTH - ANIM_TRIANGLE_BASE_OFFSET must be lower than TFT_WIDTH_MIDDLE"
#elif BLACK_LINE_WIDTH >= TFT_WIDTH_MIDDLE
#error "BLACK_LINE_WIDTH must be lower than half of tft width"
#elif ANIM_END_WIDTH_OFFSET < 0
#error "ANIM_END_WIDTH_OFFSET must be higher than 0. Check ANIM_TRIANGLE_WIDTH or ANIM_TRIANGLE_BASE_OFFSET"
#endif

#endif

#define OMNITRIX_GREEN 0xA707
#define OMNITRIX_RED 0xC000
#define OMNITRIX_GRAY 0xAD55
#define OMNITRIX_BLACK 0x0002

static bool is_animating = false;
uint32_t g_anim_start;    //Timer that helps with animation
uint8_t g_current_frame; //Frame iterator (<= 255 total frames)

//For debugging animation
#if defined ENABLE_VERBOSE_ANIM_INFO
int end_animation_time;
double avrg_frame_time;
#if defined START_ANIMATION_WITH_IMAGES
double avrg_frame_decod_time;
#endif
#endif

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
  //Set debugging animation variables for debugging animation
#if defined ENABLE_VERBOSE_ANIM_INFO
  end_animation_time;
  avrg_frame_time = 0;
#if defined START_ANIMATION_WITH_IMAGES
  avrg_frame_decod_time = 0;
#endif
#endif

}

void finish_animation() {

#if defined ALLOW_CPU_FREQ_CHANGES
  //Change cpu frequency to the default one for battery
  setCpuFrequencyMhz(DEFAULT_CPU_FREQ); //Change cpu frequency to the faster allowed one 
#endif

}
