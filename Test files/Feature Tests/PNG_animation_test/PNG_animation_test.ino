/* This program displays on the LCD screen the omnitrix start animation followed by all the alien figures displayed one after the other in a loop. 
  It is an Update to png_test
  
  Tested with: 
  ESP32-S2-Dev
  ESP32-S3 TOUCH LCD 1.28
  ESP32-S3 LCD 1.28
  
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

#define OMNITRIX_GREEN 0xA707
#define OMNITRIX_RED 0xC000
#define OMNITRIX_GRAY 0xAD55


#include "SPI.h"
#include <TFT_eSPI.h>              // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();         // Invoke custom library

#if defined START_ANIMATION_HARD_CODED
#define BLACK_LINE_WIDTH 11
#endif

int16_t xpos = 0;
int16_t ypos = 0;

//Number of aliens
int N = 11;
int Npos = 0;

void setup()
{
  //setCpuFrequencyMhz(80); //Reduce CPU Freq

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

  for (Npos = 0;Npos <= N; Npos++) {
    
    eraseAlien();
    showAlien();
    delay(1000);

  }
  
  tft.fillScreen(TFT_WHITE);
  ShowSymbols();
  delay(1000);
  tft.fillScreen(OMNITRIX_RED);
  ShowSymbols();
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
  for (xLup = -80, xLmid = 0, xLdown = -80, xRup = 320, xRmid = 240, xRdown = 320; xLup <= -5 ; xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown-- ) {
    tft.drawLine(xLup, 0, xLmid, 120, OMNITRIX_GRAY); //Draw up left part
    tft.drawLine(xLmid, 120, xLdown, 240, OMNITRIX_GRAY); //Draw down left part
    tft.drawLine(xRup, 0, xRmid, 120, OMNITRIX_GRAY); //Draw up right part
    tft.drawLine(xRmid, 120, xRdown, 240, OMNITRIX_GRAY); //Draw down right part
  }

  //Draw black lines
  for (black = 0; black <= BLACK_LINE_WIDTH; black++, xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown--) {
    tft.drawLine(xLup, 0, xLmid, 120, TFT_BLACK); //Draw up left part
    tft.drawLine(xLmid, 120, xLdown, 240, TFT_BLACK); //Draw down left part
    tft.drawLine(xRup, 0, xRmid, 120, TFT_BLACK); //Draw up right part
    tft.drawLine(xRmid, 120, xRdown, 240, TFT_BLACK); //Draw down right part
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
  uint8_t delay_time = 1;

  xLup = -6;
  xLmid = 74;
  xLdown = -6;
  xRup = 246;
  xRmid = 166;
  xRdown = 246;

  //Draw symbols up until lines don't intersect yet
  for ( ; (xLmid + BLACK_LINE_WIDTH) <= 120 ; xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown-- ) {
    //Wait
    delay(delay_time*3);
    //Draw gray lines
    tft.drawLine(xLup, 0, xLmid, 120, OMNITRIX_GRAY); //Draw up left part
    tft.drawLine(xLmid, 120, xLdown, 240, OMNITRIX_GRAY); //Draw down left part
    tft.drawLine(xRup, 0, xRmid, 120, OMNITRIX_GRAY); //Draw up right part
    tft.drawLine(xRmid, 120, xRdown, 240, OMNITRIX_GRAY); //Draw down right part
    //Draw black lines
    tft.drawLine(xLup + BLACK_LINE_WIDTH, 0, xLmid + BLACK_LINE_WIDTH, 120, TFT_BLACK); //Draw up left part
    tft.drawLine(xLmid + BLACK_LINE_WIDTH, 120, xLdown + BLACK_LINE_WIDTH, 240, TFT_BLACK); //Draw down left part
    tft.drawLine(xRup - BLACK_LINE_WIDTH, 0, xRmid - BLACK_LINE_WIDTH, 120, TFT_BLACK); //Draw up right part
    tft.drawLine(xRmid - BLACK_LINE_WIDTH, 120, xRdown - BLACK_LINE_WIDTH, 240, TFT_BLACK); //Draw down right part
  }
  //Black lines intersect with each other
  for ( ; (xLmid + BLACK_LINE_WIDTH) <= (120 + BLACK_LINE_WIDTH) ; xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown-- ) {
    //Wait
    delay(delay_time*3);
    //Draw gray lines
    tft.drawLine(xLup, 0, xLmid, 120, OMNITRIX_GRAY); //Draw up left part
    tft.drawLine(xLmid, 120, xLdown, 240, OMNITRIX_GRAY); //Draw down left part
    tft.drawLine(xRup, 0, xRmid, 120, OMNITRIX_GRAY); //Draw up right part
    tft.drawLine(xRmid, 120, xRdown, 240, OMNITRIX_GRAY); //Draw down right part
    //Draw black lines
    tft.drawLine(xLup + BLACK_LINE_WIDTH, 0, xLmid + BLACK_LINE_WIDTH, 120, TFT_BLACK); //Draw up left part
    tft.drawLine(xLmid + BLACK_LINE_WIDTH, 120, xLdown + BLACK_LINE_WIDTH, 240, TFT_BLACK); //Draw down left part
    tft.drawLine(xRup - BLACK_LINE_WIDTH, 0, xRmid - BLACK_LINE_WIDTH, 120, TFT_BLACK); //Draw up right part
    tft.drawLine(xRmid - BLACK_LINE_WIDTH, 120, xRdown - BLACK_LINE_WIDTH, 240, TFT_BLACK); //Draw down right part
  }
  //Lines intersecting
  for ( ; (xLmid + BLACK_LINE_WIDTH) <= 200 ; xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown-- ) {
    //Wait
    delay(delay_time);
    int16_t comx, comy;
    
    //Get common point of up lines
    getCommonPoint(xLup, 0, xLmid, 120, xRup, 0, xRmid, 120, &comx, &comy);
    //Draw green part of lines
    tft.drawLine(xLup, 0, xLmid, 120, OMNITRIX_GREEN); //Draw up left part
    tft.drawLine(xRup, 0, xRmid, 120, OMNITRIX_GREEN); //Draw up right part
    //Draw previous green line to clean
    tft.drawLine(xLup-1, 0, xLmid-1, 120, OMNITRIX_GREEN); //Draw up left part
    tft.drawLine(xRup+1, 0, xRmid+1, 120, OMNITRIX_GREEN); //Draw up right part
    //Draw gray part of lines
    tft.drawLine(xLup, 0, comx, comy, OMNITRIX_GRAY); //Draw up left part
    tft.drawLine(xRup, 0, comx, comy, OMNITRIX_GRAY); //Draw up right part
    //Draw previous gray line to clean
    tft.drawLine(xLup-1, 0, comx-1, comy, OMNITRIX_GRAY); //Draw up left part
    tft.drawLine(xRup+1, 0, comx+1, comy, OMNITRIX_GRAY); //Draw up right part
    
    //Get common point of down lines
    getCommonPoint(xLmid, 120, xLdown, 240, xRmid, 120, xRdown, 240, &comx, &comy);
    //Draw green part of lines
    tft.drawLine(xLmid, 120, xLdown, 240, OMNITRIX_GREEN); //Draw down left part
    tft.drawLine(xRmid, 120, xRdown, 240, OMNITRIX_GREEN); //Draw down right part
    //Draw previous green line to clean
    tft.drawLine(xLmid-1, 120, xLdown-1, 240, OMNITRIX_GREEN); //Draw down left part
    tft.drawLine(xRmid+1, 120, xRdown+1, 240, OMNITRIX_GREEN); //Draw down right part
    //Draw gray part of lines
    tft.drawLine(comx, comy, xLdown, 240, OMNITRIX_GRAY); //Draw down left part
    tft.drawLine(comx, comy, xRdown, 240, OMNITRIX_GRAY); //Draw down right part
    //Draw previous gray line to clean
    tft.drawLine(comx-1, comy, xLdown-1, 240, OMNITRIX_GRAY); //Draw down left part
    tft.drawLine(comx+1, comy, xRdown+1, 240, OMNITRIX_GRAY); //Draw down right part

    //Draw black lines
    tft.drawLine(xLup + BLACK_LINE_WIDTH, 0, xLmid + BLACK_LINE_WIDTH, 120, TFT_BLACK); //Draw up left part
    tft.drawLine(xRup - BLACK_LINE_WIDTH, 0, xRmid - BLACK_LINE_WIDTH, 120, TFT_BLACK); //Draw up right part
    tft.drawLine(xLmid + BLACK_LINE_WIDTH, 120, xLdown + BLACK_LINE_WIDTH, 240, TFT_BLACK); //Draw down left part
    tft.drawLine(xRmid - BLACK_LINE_WIDTH, 120, xRdown - BLACK_LINE_WIDTH, 240, TFT_BLACK); //Draw down right part
  }
  //Lines stop intersectiong
  for ( ; (xLmid + BLACK_LINE_WIDTH) <= 215 ; xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown-- ) {
    //Wait
    delay(delay_time*3);
    //Draw gray lines
    tft.drawLine(xLup, 0, xLmid, 120, OMNITRIX_GREEN); //Draw up left part
    tft.drawLine(xLmid, 120, xLdown, 240, OMNITRIX_GREEN); //Draw down left part
    tft.drawLine(xRup, 0, xRmid, 120, OMNITRIX_GREEN); //Draw up right part
    tft.drawLine(xRmid, 120, xRdown, 240, OMNITRIX_GREEN); //Draw down right part
    //Draw black lines
    tft.drawLine(xLup + BLACK_LINE_WIDTH, 0, xLmid + BLACK_LINE_WIDTH, 120, TFT_BLACK); //Draw up left part
    tft.drawLine(xLmid + BLACK_LINE_WIDTH, 120, xLdown + BLACK_LINE_WIDTH, 240, TFT_BLACK); //Draw down left part
    tft.drawLine(xRup - BLACK_LINE_WIDTH, 0, xRmid - BLACK_LINE_WIDTH, 120, TFT_BLACK); //Draw up right part
    tft.drawLine(xRmid - BLACK_LINE_WIDTH, 120, xRdown - BLACK_LINE_WIDTH, 240, TFT_BLACK); //Draw down right part
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

  xLup = 115;
  xLmid = 214 - BLACK_LINE_WIDTH;
  xLdown = 115;
  xRup = 125;
  xRmid = 26 + BLACK_LINE_WIDTH;
  xRdown = 125;

  for ( ; xLmid >= 120 ; xLmid--, xRmid++ ) {

    tft.drawLine(xLup, 0, xLmid, 120, OMNITRIX_GREEN); //Draw up left part
    tft.drawLine(xLmid, 120, xLdown, 240, OMNITRIX_GREEN); //Draw down left part
    tft.drawLine(xRup, 0, xRmid, 120, OMNITRIX_GREEN); //Draw up right part
    tft.drawLine(xRmid, 120, xRdown, 240, OMNITRIX_GREEN); //Draw down right part
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
  //Round to integer
  *x = (int16_t) (fx < 0 ? (fx - 0.5) : (fx + 0.5));
  *y =(int16_t) (fy < 0 ? (fy - 0.5) : (fy + 0.5));
  
  return delta;

}
#endif
