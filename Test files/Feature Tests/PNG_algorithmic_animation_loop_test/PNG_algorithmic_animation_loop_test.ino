/* This program displays on the LCD screen the omnitrix start animation followed by all the alien figures displayed one after the other in a loop. 
  It is an Update to png_test. It works with no PSRAM enabled, with 4 MB flash size and partition with 1.2 MB for APP
  
  Tested with: 
  Esp32-S2-Dev
  Esp32-S3 TOUCH LCD 1.28
  Esp32-S3 LCD 1.28
  Esp32-S3-Pico
  
  Add Setup302_ESP32S3_GC9A01_TOUCH.h and Setup303_OMNITRIX_CUSTOM.h in libraries\TFT_eSPI\User_Setups

  Use one of these header files in User_Setup_Select.h 
  #include <User_Setups/Setup302_ESP32S3_GC9A01_TOUCH.h>
  #include <User_Setups/Setup303_OMNITRIX_CUSTOM.h>
*/

//ANIMATION SETTINGS: Choose only one method for showing animation
//1. Start animation with images
//#define START_ANIMATION_WITH_IMAGES //Has memory leaks
//2. Hard coded start animation
#define START_ANIMATION_HARD_CODED //Slow but low memory and smooth

#include <PNGdec.h>

// Include image array
#include "omnitrix_aliens.h"
#if defined START_ANIMATION_WITH_IMAGES
#include "omnitrix_alien_backround.h"
#include "omnitrix_anim_png_circle.h"
#endif

PNG png; // PNG decoder instance

#define MAX_IMAGE_WDITH 240 // Sets rendering line buffer lengths, adjust for your images

//Site for RGB565: https://rgbcolorpicker.com/565

//#define OMNITRIX_GREEN 0xA707 //default
#define OMNITRIX_GREEN 0x07e0
#define OMNITRIX_RED 0xC000 //default
//#define OMNITRIX_GRAY 0xAD55 //default
#define OMNITRIX_GRAY 0x8c50
//#define OMNITRIX_BLACK TFT_BLACK //default
#define OMNITRIX_BLACK 0x0002


#include "SPI.h"
#include <TFT_eSPI.h>              // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();         // Invoke custom library

#if defined START_ANIMATION_HARD_CODED

//Animation configuration
#define TFT_WIDTH_USED 240 //120 // 240 //default
#define TFT_HEIGHT_USED 240 //120 // 240 //default

#define ANIM_TRIANGLE_WIDTH 74 //default, must be lower than TFT_WIDTH_MIDDLE
//#define ANIM_TRIANGLE_WIDTH 80 
//#define ANIM_TRIANGLE_WIDTH 40
#define ANIM_TRIANGLE_BASE_OFFSET -6 //default
//#define ANIM_TRIANGLE_BASE_OFFSET 0
#define ANIM_TRIANGLE_PIXELS_TRAVEL 215 //default, must be lower than TFT_WIDTH_USED and higher than TFT_WIDTH_MIDDLE+ANIM_TRIANGLE_WIDTH
//#define ANIM_TRIANGLE_PIXELS_TRAVEL 80
//#define ANIM_TRIANGLE_PIXELS_TRAVEL 300

#define BLACK_LINE_WIDTH 11 //default
//#define BLACK_LINE_WIDTH 16

//Automatically calculated animation values
#define TFT_WIDTH_MIDDLE (TFT_WIDTH_USED/2) //120 in default
#define TFT_HEIGHT_MIDDLE (TFT_HEIGHT_USED/2) //120 in default
// 80 in default
#define ANIM_TRIANGLE_START_LEFT_OFFSET (ANIM_TRIANGLE_WIDTH - ANIM_TRIANGLE_BASE_OFFSET)
// 320 in default
#define ANIM_TRIANGLE_START_RIGHT_OFFSET (ANIM_TRIANGLE_WIDTH - ANIM_TRIANGLE_BASE_OFFSET + TFT_WIDTH_USED)
// 10 in default
//#define ANIM_END_WIDTH_OFFSET (ANIM_TRIANGLE_PIXELS_TRAVEL-BLACK_LINE_WIDTH-ANIM_TRIANGLE_WIDTH-TFT_WIDTH_MIDDLE)
// 8 in default
#define ANIM_END_WIDTH_OFFSET 2*(ANIM_TRIANGLE_PIXELS_TRAVEL-BLACK_LINE_WIDTH-ANIM_TRIANGLE_START_LEFT_OFFSET-TFT_WIDTH_MIDDLE)
//#define ANIM_SELECT_SYM_END (TFT_WIDTH_USED- ANIM_TRIANGLE_PIXELS_TRAVEL-BLACK_LINE_WIDTH-ANIM_TRIANGLE_WIDTH)
//#define ANIM_END_WIDTH_OFFSET (TFT_WIDTH_USED-(ANIM_SELECT_SYM_END*2))

#endif

int16_t xpos = 0;
int16_t ypos = 0;

//Number of aliens
int N = 11;
int Npos = 0;

void setup()
{
  setCpuFrequencyMhz(80); //Reduce CPU Freq
  //setCpuFrequencyMhz(160); //Reduce CPU Freq

  Serial.begin(115200);
  Serial.println("\n\n Using the PNGdec library");

  // Initialise the TFT
  tft.begin();
  tft.fillScreen(OMNITRIX_GREEN);
  ShowSymbols();

  Serial.println("\r\nInitialisation done.");

}


void loop()
{

  showAnimation();
  delay(1000);

  for (Npos = 0;Npos <= 0; Npos++) {
  //Npos <= N; Npos++) {
    
    eraseAlien();
    showAlien();
    delay(100);

  }
  delay(1000);
  // eraseAlien();
  // delay(1000);
  // Npos=0;
  // showAlien();
  // eraseAlienWithDirection(true); //left to right
  // delay(1000);
  // showAlien();
  // eraseAlienWithDirection(false); //right to left
  // delay(1000);
  /*
  tft.fillScreen(TFT_WHITE);
  ShowSymbols();
  delay(1000);
  tft.fillScreen(OMNITRIX_RED);
  ShowSymbols();
  delay(1000);*/
  tft.fillScreen(OMNITRIX_GREEN);
  delay(1000);
  showSelectSymbols();
  delay(1000);
  tft.fillScreen(OMNITRIX_GREEN);
  ShowSymbols();
 
}

//Function that displays start icon symbols
void ShowSymbols() {

  //Serial.println("show symbols");

  //Start Symbols with images
  #if defined START_ANIMATION_WITH_IMAGES

  int16_t rc = png.openFLASH((uint8_t *)omnitrix_anim[0], sizeof(omnitrix_anim[0]), pngDraw);

  if (rc == PNG_SUCCESS) {
    //Serial.println("Successfully png file");

    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }



  //Hard coded start symbols
  #elif defined START_ANIMATION_HARD_CODED

  int16_t xLup, xLmid, xLdown, xRup, xRmid, xRdown, black;

  //Draw gray symbols
  for (xLup = -ANIM_TRIANGLE_START_LEFT_OFFSET, xLmid = 0, xLdown = -ANIM_TRIANGLE_START_LEFT_OFFSET, 
  xRup = ANIM_TRIANGLE_START_RIGHT_OFFSET, xRmid = TFT_WIDTH_USED, xRdown = ANIM_TRIANGLE_START_RIGHT_OFFSET; 
  xLmid <= ANIM_TRIANGLE_WIDTH ; 
  xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown-- ) {
    tft.drawLine(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, OMNITRIX_GRAY); //Draw up left part
    tft.drawLine(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down left part
    tft.drawLine(xRup, 0, xRmid, TFT_HEIGHT_MIDDLE, OMNITRIX_GRAY); //Draw up right part
    tft.drawLine(xRmid, TFT_HEIGHT_MIDDLE, xRdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down right part

    //delay(50);
  }

  //Draw black lines
  for (black = 0; black <= BLACK_LINE_WIDTH; black++, xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown--) {
    tft.drawLine(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up left part
    tft.drawLine(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down left part
    tft.drawLine(xRup, 0, xRmid, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up right part
    tft.drawLine(xRmid, TFT_HEIGHT_MIDDLE, xRdown, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down right part
  }

  #endif
 
}

void showSelectSymbols() {

  //Start Symbols with images
  #if defined START_ANIMATION_WITH_IMAGES

  int16_t rc = png.openFLASH((uint8_t *)omnitrix_anim[omnitrix_anim_N], sizeof(omnitrix_anim[omnitrix_anim_N]), pngDraw);

  if (rc == PNG_SUCCESS) {
    //Serial.println("Successfully png file");

    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }

  //Hard coded start symbols
  #elif defined START_ANIMATION_HARD_CODED

  int16_t xLup, xLmid, xLdown, xRup, xRmid, xRdown, black;

  Serial.print("xLup <= ");
  Serial.println((TFT_WIDTH_MIDDLE-(ANIM_END_WIDTH_OFFSET/2)-BLACK_LINE_WIDTH));
    
  xLup = 0;
  xLmid = (-ANIM_TRIANGLE_START_LEFT_OFFSET);
  xLdown = 0; 
  xRup = TFT_HEIGHT_USED; 
  xRmid = ANIM_TRIANGLE_START_RIGHT_OFFSET;
  xRdown = TFT_HEIGHT_USED;

  //Draw gray symbols
  //-1 because the last line points in showAnimation are located at the first black line after the green part
  for (; xLup <= (TFT_WIDTH_MIDDLE-(ANIM_END_WIDTH_OFFSET/2)-BLACK_LINE_WIDTH-1);
  xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown-- ) {
    tft.drawLine(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, OMNITRIX_GRAY); //Draw up left part
    tft.drawLine(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down left part
    tft.drawLine(xRup, 0, xRmid, TFT_HEIGHT_MIDDLE, OMNITRIX_GRAY); //Draw up right part
    tft.drawLine(xRmid, TFT_HEIGHT_MIDDLE, xRdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down right part

    //delay(50);
    
    //Show points for last frame
    if ( xLup == (TFT_WIDTH_MIDDLE-(ANIM_END_WIDTH_OFFSET/2)-BLACK_LINE_WIDTH-1) ) {
      Serial.printf("Selectsym: xLup: %d, xLmid: %d, xLdown: %d, xRup: %d, xRmid: %d, xRdown: %d\n", xLup, xLmid, xLdown, xRup, xRmid, xRdown);
    }
  }

  //Draw black lines
  for (black = 0; black <= BLACK_LINE_WIDTH; black++, xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown--) {
    tft.drawLine(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up left part
    tft.drawLine(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down left part
    tft.drawLine(xRup, 0, xRmid, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up right part
    tft.drawLine(xRmid, TFT_HEIGHT_MIDDLE, xRdown, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down right part

    delay(50);
  }

  #endif
}

void showAnimation() {

  //Start Symbols with image
  #if defined START_ANIMATION_WITH_IMAGES

  uint8_t frame = 0;
  uint8_t delay_time = 40;

  for (; frame <= omnitrix_anim_N; frame++)  {
    
    delay(delay_time);
    
    //Serial.println(frame);
    int16_t rc = png.openFLASH((uint8_t *)omnitrix_anim[frame], sizeof(omnitrix_anim[frame]), pngDraw);

    //if (rc = PNG_SUCCESS) {
      tft.startWrite();
      rc = png.decode(NULL, 0);
      tft.endWrite();
    //}

  }


  //Hard coded animation
  #elif defined START_ANIMATION_HARD_CODED

  int16_t xLup, xLmid, xLdown, xRup, xRmid, xRdown;
  uint8_t delay_time = 4;

  xLup = ANIM_TRIANGLE_BASE_OFFSET;
  xLmid = ANIM_TRIANGLE_WIDTH;
  xLdown = ANIM_TRIANGLE_BASE_OFFSET;
  xRup = TFT_WIDTH_USED - ANIM_TRIANGLE_BASE_OFFSET;
  xRmid = TFT_WIDTH_USED - ANIM_TRIANGLE_WIDTH;
  xRdown = TFT_WIDTH_USED - ANIM_TRIANGLE_BASE_OFFSET;

  //Draw symbols up until lines don't intersect yet
  for ( ; (xLmid + BLACK_LINE_WIDTH) <= TFT_WIDTH_MIDDLE ; xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown-- ) {
    //Wait
    //delay(delay_time);

    tft.startWrite();

    //Draw gray lines
    tft.drawLine(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, OMNITRIX_GRAY); //Draw up left part
    tft.drawLine(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down left part
    tft.drawLine(xRup, 0, xRmid, TFT_HEIGHT_MIDDLE, OMNITRIX_GRAY); //Draw up right part
    tft.drawLine(xRmid, TFT_HEIGHT_MIDDLE, xRdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down right part
    //Draw black lines
    tft.drawLine(xLup + BLACK_LINE_WIDTH, 0, xLmid + BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up left part
    tft.drawLine(xLmid + BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xLdown + BLACK_LINE_WIDTH, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down left part
    tft.drawLine(xRup - BLACK_LINE_WIDTH, 0, xRmid - BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up right part
    tft.drawLine(xRmid - BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xRdown - BLACK_LINE_WIDTH, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down right part

    tft.endWrite();
  }
  //Black lines intersect with each other until their middle
  for ( ; (xLmid + BLACK_LINE_WIDTH) <= (TFT_WIDTH_MIDDLE + BLACK_LINE_WIDTH/2) ; xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown-- ) {
    //Wait
    //delay(delay_time);
    int16_t comx, comy;
    
    //get common point of the lines: left up to mid gray part and right up to mid black part
    //getCommonPoint(xLup, 0, xLmid, 120, xRup-BLACK_LINE_WIDTH, 0, xRmid-BLACK_LINE_WIDTH, 120, &comx, &comy);

    tft.startWrite();

    //Draw gray up lines
    tft.drawLine(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, OMNITRIX_GRAY); //Draw up left part
    tft.drawLine(xRup, 0, xRmid, TFT_HEIGHT_MIDDLE, OMNITRIX_GRAY); //Draw up right part
    //Draw black up lines
    tft.drawLine(xLup + BLACK_LINE_WIDTH, 0, xLmid + BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up left part
    tft.drawLine(xRup - BLACK_LINE_WIDTH, 0, xRmid - BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up right part
    
    //get common point of the lines: left mid to down gray part and right mid to down black part
    //getCommonPoint(xLmid, 120, xLdown, 240, xRmid-BLACK_LINE_WIDTH, 120, xRdown-BLACK_LINE_WIDTH, 240, &comx, &comy);
    
    //Draw gray down lines
    tft.drawLine(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down left part
    tft.drawLine(xRmid, TFT_HEIGHT_MIDDLE, xRdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down right part
    //Draw black down lines
    tft.drawLine(xLmid + BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xLdown + BLACK_LINE_WIDTH, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down left part
    tft.drawLine(xRmid - BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xRdown - BLACK_LINE_WIDTH, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down right part

    tft.endWrite();

    //delay(300);
  }
  //Black lines intersect with each other until their end
  for ( ; (xLmid + BLACK_LINE_WIDTH) <= (TFT_WIDTH_MIDDLE + BLACK_LINE_WIDTH) ; xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown-- ) {
    //Wait
    //delay(delay_time);
    int16_t comx, comy;
    
    //get common point of the lines: upper left to mid gray part and upper right to mid black part
    getCommonPoint(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, xRup-BLACK_LINE_WIDTH, 0, xRmid-BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, &comx, &comy);

    tft.startWrite();

    //Draw gray up lines
    tft.drawLine(xLup, 0, comx, comy, OMNITRIX_GRAY); //Draw up left part
    tft.drawLine(xRup, 0, (TFT_WIDTH_USED-comx), comy, OMNITRIX_GRAY); //Draw up right part
    //Draw previous gray line to clean
    tft.drawLine(xLup-1, 0, comx-1, comy, OMNITRIX_GRAY); //Draw up left part
    tft.drawLine(xRup+1, 0, (TFT_WIDTH_USED-comx)+1, comy, OMNITRIX_GRAY); //Draw up right part
    //Draw black up lines
    tft.drawLine(xLup + BLACK_LINE_WIDTH, 0, xLmid + BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up left part
    tft.drawLine(xRup - BLACK_LINE_WIDTH, 0, xRmid - BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up right part
    
    //get common point of the lines: left mid to lower gray part and right mid to lower black part
    getCommonPoint(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, 
    xRmid-BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xRdown-BLACK_LINE_WIDTH, TFT_HEIGHT_USED, &comx, &comy);
    
    //Draw gray down lines
    tft.drawLine(comx, comy, xLdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down left part
    tft.drawLine((TFT_WIDTH_USED-comx), comy, xRdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down right part
    //Draw previous gray line to clean
    tft.drawLine(comx-1, comy, xLdown-1, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down left part
    tft.drawLine((TFT_WIDTH_USED-comx)+1, comy, xRdown+1, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down right part
    //Draw black down lines
    tft.drawLine(xLmid + BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xLdown + BLACK_LINE_WIDTH, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down left part
    tft.drawLine(xRmid - BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xRdown - BLACK_LINE_WIDTH, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down right part

    tft.endWrite();

    //delay(300);
  }
  //Gray triangle lines intersecting
  for ( ; (xLmid + BLACK_LINE_WIDTH) <= (TFT_WIDTH_MIDDLE + ANIM_TRIANGLE_START_LEFT_OFFSET) + BLACK_LINE_WIDTH ; 
  xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown-- ) {
    //Wait
    //delay(delay_time);
    int16_t comx, comy;
    
    //Clean the previous black line artifacts by covering them with green lines
    //Get common upper point of intersecting middle x lines
    getCommonPoint(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, xRup, 0, xRmid, TFT_HEIGHT_MIDDLE, &comx, &comy);

    tft.startWrite();

    //Draw green part of lines
    tft.drawLine(comx, comy, xLmid-1, TFT_HEIGHT_MIDDLE, OMNITRIX_GREEN); //Draw up left part
    tft.drawLine(comx, comy, xRmid+1, TFT_HEIGHT_MIDDLE, OMNITRIX_GREEN); //Draw up right part
    //Draw previous green line to clean
    tft.drawLine(comx-1, comy, xLmid-2, TFT_HEIGHT_MIDDLE, OMNITRIX_GREEN); //Draw up left part
    tft.drawLine(comx+1, comy, xRmid+2, TFT_HEIGHT_MIDDLE, OMNITRIX_GREEN); //Draw up right part

    //This makes sure the upper right and left lines intersecting on the gray to black part have the right point
    //get common point of the lines: upper left to mid gray part and upper right to mid black part
    getCommonPoint(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, xRup-BLACK_LINE_WIDTH, 0, xRmid-BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, &comx, &comy);
    
    //Draw gray part of lines
    tft.drawLine(xLup-1, 0, comx, comy, OMNITRIX_GRAY); //Draw up left part
    tft.drawLine(xRup+1, 0, (TFT_WIDTH_USED-comx), comy, OMNITRIX_GRAY); //Draw up right part  purple 0x780F
    //Draw previous gray line to clean
    tft.drawLine(xLup-2, 0, comx-1, comy, OMNITRIX_GRAY); //Draw up left part
    tft.drawLine(xRup+2, 0, (TFT_WIDTH_USED-comx)+1, comy, OMNITRIX_GRAY); //Draw up right part

    

    //Get common lower point of intersecting middle x lines
    getCommonPoint(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, 
    xRmid, TFT_HEIGHT_MIDDLE, xRdown, TFT_HEIGHT_USED, &comx, &comy);
/*
    tft.fillTriangle(xLmid, 120, xLdown, 240, xLmid-1, 120, OMNITRIX_GREEN);
    tft.fillTriangle(xRmid, 120, xRdown, 240, xRmid+1, 120, OMNITRIX_GREEN);

    tft.fillTriangle(comx, comy, xLdown, 240, comx-1, comy, OMNITRIX_GRAY);
    tft.fillTriangle(comx, comy, xRdown, 240, comx+1, comy, OMNITRIX_GRAY);
*/    
    //Draw green part of lines
    tft.drawLine(xLmid-1, TFT_HEIGHT_MIDDLE, comx, comy, OMNITRIX_GREEN); //Draw down left part
    tft.drawLine(xRmid+1, TFT_HEIGHT_MIDDLE, comx, comy, OMNITRIX_GREEN); //Draw down right part
    //Draw previous green line to clean
    tft.drawLine(xLmid-1, TFT_HEIGHT_MIDDLE, comx-1, comy, OMNITRIX_GREEN); //Draw down left part
    tft.drawLine(xRmid+1, TFT_HEIGHT_MIDDLE, comx+1, comy, OMNITRIX_GREEN); //Draw down right part

    //This makes sure the lower right and left lines intersecting on the gray to black part have the right point
    //get common point of the lines: left mid to lower gray part and right mid to lower black part
    getCommonPoint(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, 
    xRmid-BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xRdown-BLACK_LINE_WIDTH, TFT_HEIGHT_USED, &comx, &comy);

    //Draw gray part of lines
    tft.drawLine(comx, comy, xLdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down left part
    tft.drawLine((TFT_WIDTH_USED-comx), comy, xRdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down right part
    //Draw previous gray line to clean
    tft.drawLine(comx-1, comy, xLdown-1, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down left part
    tft.drawLine((TFT_WIDTH_USED-comx)+1, comy, xRdown+1, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down right part
    

    //Draw black lines
    tft.drawLine(xLup + BLACK_LINE_WIDTH, 0, xLmid + BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up left part
    tft.drawLine(xRup - BLACK_LINE_WIDTH, 0, xRmid - BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up right part
    tft.drawLine(xLmid + BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xLdown + BLACK_LINE_WIDTH, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down left part
    tft.drawLine(xRmid - BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xRdown - BLACK_LINE_WIDTH, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down right part
    
    /*
    tft.drawPixel(comx, comy, 0x780F);
    tft.drawPixel(comx, comy+1, 0x780F);
    tft.drawPixel(comx, comy-1, 0x780F);
    tft.drawPixel(comx, comy+2, 0x780F);
    tft.drawPixel(comx, comy-2, 0x780F);
    */

    tft.endWrite();

    //delay(100);
  }
  
  //Lines stop intersectiong (up to 215 from middle left point)
  //xLmid by itself is at the first black line
  for ( ; (xLmid + BLACK_LINE_WIDTH) <= ANIM_TRIANGLE_PIXELS_TRAVEL ; xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown-- ) {
    //Wait
    //delay(delay_time);

    tft.startWrite();

    //Draw green lines
    tft.drawLine(xLup-1, 0, xLmid-1, TFT_HEIGHT_MIDDLE, OMNITRIX_GREEN); //Draw up left part
    tft.drawLine(xLmid-1, TFT_HEIGHT_MIDDLE, xLdown-1, TFT_HEIGHT_USED, OMNITRIX_GREEN); //Draw down left part
    tft.drawLine(xRup+1, 0, xRmid+1, TFT_HEIGHT_MIDDLE, OMNITRIX_GREEN); //Draw up right part
    tft.drawLine(xRmid+1, TFT_HEIGHT_MIDDLE, xRdown-1, TFT_HEIGHT_USED, OMNITRIX_GREEN); //Draw down right part
    //Draw black lines
    tft.drawLine(xLup + BLACK_LINE_WIDTH, 0, xLmid + BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up left part
    tft.drawLine(xLmid + BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xLdown + BLACK_LINE_WIDTH, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down left part
    tft.drawLine(xRup - BLACK_LINE_WIDTH, 0, xRmid - BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up right part
    tft.drawLine(xRmid - BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xRdown - BLACK_LINE_WIDTH, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down right part

    tft.endWrite();

    //Show points for last frame
    if ((xLmid + BLACK_LINE_WIDTH) == ANIM_TRIANGLE_PIXELS_TRAVEL) {
      Serial.printf("xLup: %d, xLmid: %d, xLdown: %d, xRup: %d, xRmid: %d, xRdown: %d\n", xLup, xLmid, xLdown, xRup, xRmid, xRdown);
    }
    //delay(300);
  }

  #endif

}


void showAlien() {

  uint16_t pngw = 0, pngh = 0; // To store width and height of image

  int16_t rc = png.openFLASH((uint8_t *)omnitrix_aliens[Npos], sizeof(omnitrix_aliens[Npos]), pngDraw);

  if (rc == PNG_SUCCESS) {
    Serial.println("Successfully png file");
    pngw = png.getWidth();
    pngh = png.getHeight();
    Serial.printf("Image metrics: (%d x %d), %d bpp, pixel type: %d\n", pngw, pngh, png.getBpp(), png.getPixelType());

    tft.startWrite();
    uint32_t dt = millis();
    rc = png.decode(NULL, 0);
    tft.endWrite();
    Serial.print(millis() - dt); Serial.println("ms");
    tft.endWrite();

    // png.close(); // Required for files, not needed for FLASH arrays
  }

}

void eraseAlien() {
  
  #ifdef START_ANIMATION_WITH_IMAGES
  uint16_t pngw = 0, pngh = 0; // To store width and height of image

  int16_t rc2 = png.openFLASH((uint8_t *)omnitrix_alien_backround, sizeof(omnitrix_alien_backround), pngDraw);

  if (rc2 == PNG_SUCCESS) {
    Serial.println("Successfully png file");
    pngw = png.getWidth();
    pngh = png.getHeight();
    Serial.printf("Image metrics: (%d x %d), %d bpp, pixel type: %d\n", pngw, pngh, png.getBpp(), png.getPixelType());

    tft.startWrite();
    uint32_t dt = millis();
    rc2 = png.decode(NULL, 0);
    tft.endWrite();
    Serial.print(millis() - dt); Serial.println("ms");
    tft.endWrite();

    // png.close(); // Required for files, not needed for FLASH arrays
  }

  #elif defined START_ANIMATION_HARD_CODED

  int16_t xLup, xLmid, xLdown, xRup, xRmid, xRdown;

  xLup = TFT_WIDTH_MIDDLE - ((ANIM_END_WIDTH_OFFSET-2)/2);
  xLmid = (TFT_WIDTH_USED-ANIM_TRIANGLE_PIXELS_TRAVEL+1 + BLACK_LINE_WIDTH);
  xLdown = TFT_WIDTH_MIDDLE - ((ANIM_END_WIDTH_OFFSET-2)/2);
  xRup = TFT_WIDTH_MIDDLE + ((ANIM_END_WIDTH_OFFSET-2)/2);
  xRmid = (ANIM_TRIANGLE_PIXELS_TRAVEL-1 - BLACK_LINE_WIDTH); 
  xRdown = TFT_WIDTH_MIDDLE + ((ANIM_END_WIDTH_OFFSET-2)/2);

  Serial.printf("Erase: xLup: %d, xLmid: %d, xLdown: %d, xRup: %d, xRmid: %d, xRdown: %d\n", xLup, xLmid, xLdown, xRup, xRmid, xRdown);

  // Draw the cleaning up to where the symbols end
  for ( ; xLmid <= xLup ; xLmid++, xRmid-- ) {

    tft.drawLine(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, OMNITRIX_GREEN); //Draw up left part purple 0x780F
    tft.drawLine(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, OMNITRIX_GREEN); //Draw down left part OMNITRIX_GREEN
    tft.drawLine(xRup, 0, xRmid, TFT_HEIGHT_MIDDLE, OMNITRIX_GREEN); //Draw up right part
    tft.drawLine(xRmid, TFT_HEIGHT_MIDDLE, xRdown, TFT_HEIGHT_USED, OMNITRIX_GREEN); //Draw down right part

    //delay(100);
  }
  // Draw the cleaning to the rest of the space
  for (; xLmid <= TFT_WIDTH_MIDDLE; xLmid++,xRmid--) {

    tft.drawLine(xLmid, 0, xLmid, TFT_HEIGHT_USED, OMNITRIX_GREEN); //Draw left to right part
    tft.drawLine(xRmid, 0, xRmid, TFT_HEIGHT_USED, OMNITRIX_GREEN); //Draw right to left part

    //delay(100);
  }

  #endif

}

void eraseAlienWithDirection(bool left_to_rightDir) {

  #ifdef START_ANIMATION_WITH_IMAGES

  eraseAlien();

  #elif defined START_ANIMATION_HARD_CODED

  int16_t xLup, xLmid, xLdown, xRup, xRmid, xRdown;
  int16_t startXup, startXmid, startXdown, endXup, endXmid, endXdown;
  int8_t step;

  xLup = TFT_WIDTH_MIDDLE - ((ANIM_END_WIDTH_OFFSET-2)/2);
  xLmid = (TFT_WIDTH_USED-ANIM_TRIANGLE_PIXELS_TRAVEL+1 + BLACK_LINE_WIDTH);
  xLdown = TFT_WIDTH_MIDDLE - ((ANIM_END_WIDTH_OFFSET-2)/2);
  xRup = TFT_WIDTH_MIDDLE + ((ANIM_END_WIDTH_OFFSET-2)/2);
  xRmid = (ANIM_TRIANGLE_PIXELS_TRAVEL-1 - BLACK_LINE_WIDTH); 
  xRdown = TFT_WIDTH_MIDDLE + ((ANIM_END_WIDTH_OFFSET-2)/2);

  //Left to Right
  if (left_to_rightDir) {
    startXup = xLup;
    startXmid = xLmid;
    startXdown = xLdown;
    endXup = xRup;
    endXmid = xRmid;
    endXdown = xRdown;
    step = 1;

  //Right to Left
  } else {
    startXup = xRup;
    startXmid = xRmid;
    startXdown = xRdown;
    endXup = xLup;
    endXmid = xLmid;
    endXdown = xLdown;
    step = -1;
  }

  //Draw from left to right
  // Draw the cleaning up to where the left symbols end
  for ( ; (startXmid * step) <= (startXup * step) ; startXmid+=step ) {
    tft.drawLine(startXup, 0, startXmid, TFT_HEIGHT_MIDDLE, OMNITRIX_GREEN); //Draw up left part purple 0x780F
    tft.drawLine(startXmid, TFT_HEIGHT_MIDDLE, startXdown, TFT_HEIGHT_USED, OMNITRIX_GREEN); //Draw down left part 

    //delay(50);
  }
  
  //Draw the cleaning up to where the right symbols start
  for (; (startXmid * step) <= (endXup * step); startXmid+=step) {

    tft.drawLine(startXmid, 0, startXmid, TFT_HEIGHT_USED, OMNITRIX_GREEN); //Draw left to right part

    //delay(50);
  }

  // Draw the cleaning up to where the right symbols end
  for ( ; (startXmid * step) <= (endXmid * step) ; startXmid+=step ) {
    tft.drawLine(endXup, 0, startXmid, TFT_HEIGHT_MIDDLE, OMNITRIX_GREEN); //Draw up left part purple 0x780F
    tft.drawLine(startXmid, TFT_HEIGHT_MIDDLE, endXdown, TFT_HEIGHT_USED, OMNITRIX_GREEN); //Draw down left part OMNITRIX_GREEN

    //delay(50);
  }

  #endif
}

#if defined START_ANIMATION_HARD_CODED
//Find common point of lines A[(Ax1, Ay1),(Ax2, Ay2)] and B[(Bx1, By1),(Bx2, By2)]
float getCommonPoint(int16_t Ax1, int16_t Ay1, int16_t Ax2, int16_t Ay2, int16_t Bx1, int16_t By1, int16_t Bx2, int16_t By2, int16_t* x, int16_t* y) {

  //For line equations y = Aa*x + Ab, y = Ba*x + Bb
  float Aa, Ba, Ab, Bb; 
  //Common point calculated in float
  float fx, fy;

  //Find A's equation
  Aa = (float) (Ay2 - Ay1)/ (Ax2 - Ax1); //slope a
  Ab = (float) Ay1 - Aa*Ax1; //b = y1 - ax1
  //y = Aa*x + Ab
  
  //Find B's equation
  Ba = (float) (By2 - By1)/ (Bx2 - Bx1);  //slope a
  Bb = (float) By1 - Ba*Bx1; //b = y1 - ax1
  //y = Ba*x + Bb

  //Find delta
  float delta = Aa * (-1) - Ba * (-1);

  //float delta = ((float) (Ay2 - Ay1)/ (Ax2 - Ax1)) * (-1) - ((float) (By2 - By1)/ (Bx2 - Bx1)) * (-1);

  //Check delta
  if (delta == 0) {
    //Serial.println("Lines are parallel");
    *x = 0;
    *y = 0;
    return delta;
  }

  //Find common point
  fx = -((-1) * Ab - (-1) * Bb) / delta;
  fy = -(Aa * Bb - Ba * Ab) / delta;

  //Find common point
  //fx = -((-1) * ((float) Ay1 - ((float) (Ay2 - Ay1)/ (Ax2 - Ax1))*Ax1) - (-1) * ((float) By1 - ((float) (By2 - By1)/ (Bx2 - Bx1))*Bx1)) / delta;
  //fy = -(((float) (Ay2 - Ay1)/ (Ax2 - Ax1)) * ((float) By1 - ((float) (By2 - By1)/ (Bx2 - Bx1))*Bx1) - ((float) (By2 - By1)/ (Bx2 - Bx1)) * ((float) Ay1 - ((float) (Ay2 - Ay1)/ (Ax2 - Ax1))*Ax1)) / delta;

  //Round to integer
  //*x = (int16_t) (fx < 0 ? (fx - 0.5) : (fx + 0.5));
  //*y =(int16_t) (fy < 0 ? (fy - 0.5) : (fy + 0.5));

  //Round to integer
  *x = (int16_t) fx;
  *y =(int16_t) fy;


  return delta;

}
#endif
