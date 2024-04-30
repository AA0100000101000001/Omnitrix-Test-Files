/* This program displays on the LCD screen the omnitrix start animation followed by all the alien figures displayed one after the other in a loop. 
  It is an Update to png_test
  
  Tested with: 
  ESP32-S2-Dev
  ESP32-S3 TOUCH LCD 1.28
  
  Add Setup302_ESP32S3_GC9A01_TOUCH.h and Setup303_OMNITRIX_CUSTOM.h in libraries\TFT_eSPI\User_Setups

  Use one of these header files in User_Setup_Select.h 
  #include <User_Setups/Setup302_ESP32S3_GC9A01_TOUCH.h>
  #include <User_Setups/Setup303_OMNITRIX_CUSTOM.h>
*/

//ANIMATION SETTINGS: Choose only one method for showing animation
//1. Start animation with images
//#define START_ANIMATION_WITH_IMAGES //Has memory leaks
//2. Hard coded start animation
#define START_ANIMATION_HARD_CODED //Not finished

#include <PNGdec.h>

// Include image array
#include "omnitrix_aliens.h"
#include "omnitrix_alien_backround.h"
#if defined START_ANIMATION_WITH_IMAGES
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
//TFT sprites
TFT_eSprite upLine = TFT_eSprite(&tft);
TFT_eSprite downLine = TFT_eSprite(&tft);
#define BLACK_LINE_WIDTH 11
#endif

int16_t xpos = 0;
int16_t ypos = 0;

//Number of aliens
int N = 11;
int Npos = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\n Using the PNGdec library");

  
#if defined START_ANIMATION_HARD_CODED
//Initialise up line sprite
  upLine.setColorDepth(8);
  upLine.createSprite(40, 60);

  upLine.fillSprite(TFT_TRANSPARENT);

  //Initialise down line sprite
  downLine.setColorDepth(8);
  downLine.createSprite(40, 60);

  downLine.fillSprite(TFT_TRANSPARENT);
#endif

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

  int XLup1, XLup2, YLup1, YLup2, XLdown1, XLdown2, YLdown1, YLdown2;
  int XRup1, XRup2, YRup1, YRup2, XRdown1, XRdown2, YRdown1, YRdown2;
  int black;


  upLine.drawLine(0, 0, 40, 60, OMNITRIX_GRAY);
  downLine.drawLine(40, 0, 0, 60, OMNITRIX_GRAY);

  //draw down and upper left symbol
  XLup1 = -80;
  YLup1 = 0;
  XLdown1 = -40;
  YLdown1 = 119;
  XLup2 = -40;  //x=80*y/120
  YLup2 = 60;   //y=x*120/80
  XLdown2 = -80;
  YLdown2 = 178;
  //draw down and upper right symbol
  XRup1 = 240;  //240-80
  YRup1 = 120;
  XRdown1 = 280;
  YRdown1 = 1;
  YRup2 = 180;
  XRup2 = 280;
  XRdown2 = 240;
  YRdown2 = 60;
  for (; XLup1 <= -5 | XLup2 <= 35 | XRup1 >= 315; XLup1++, XLdown1++, XLup2++, XLdown2++, XRup1--, XRdown1--, XRup2--, XRdown2--) {
    upLine.pushSprite(XLup1, YLup1, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown1, YLdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XLup2, YLup2, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown2, YLdown2, TFT_TRANSPARENT);
    upLine.pushSprite(XRup1, YRup1, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown1, YRdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XRup2, YRup2, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown2, YRdown2, TFT_TRANSPARENT);
  }

  //draw black lines
  upLine.drawLine(0, 0, 40, 60, TFT_BLACK);
  downLine.drawLine(40, 0, 0, 60, TFT_BLACK);
  for (black = 0; black <= BLACK_LINE_WIDTH; black++, XLup1++, XLdown1++, XLup2++, XLdown2++, XRup1--, XRdown1--, XRup2--, XRdown2--) {
    upLine.pushSprite(XLup1, YLup1, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown1, YLdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XLup2, YLup2, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown2, YLdown2, TFT_TRANSPARENT);
    upLine.pushSprite(XRup1, YRup1, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown1, YRdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XRup2, YRup2, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown2, YRdown2, TFT_TRANSPARENT);
  }

  #endif
 
}

void showAnimation() {

  //Start Symbols with image
  #if defined START_ANIMATION_WITH_IMAGES

  int frame = 0;
  int fps = 40;

  for (; frame <= omnitrix_anim_N; frame++)  {
    
    delay(fps);
    
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

  int XLup1, XLup2, YLup1, YLup2, XLdown1, XLdown2, YLdown1, YLdown2;
 int XRup1, XRup2, YRup1, YRup2, XRdown1, XRdown2, YRdown1, YRdown2;
 int black;
 int speed = 1;
 //upLine.drawLine(0, 0, 40, 60, OMNITRIX_GRAY);
 //downLine.drawLine(40, 0, 0, 60, OMNITRIX_GRAY);

 //upLine.drawLine(0, 0, 40, 60, OMNITRIX_RED);
 //downLine.drawLine(40, 0, 0, 60, OMNITRIX_RED);
 //Start coordinates
 //offset = +86 for left symbols, -86 for right symbols
 XLup1 = 6;
 YLup1 = 1;
 XLdown1 = 46;
 YLdown1 = 119;
 XLup2 = 46; //= 80 - 40 + 6, 60 = sprite width + 46 = 106 Symbol end
 YLup2 = 60;
 XLdown2 = 6;
 YLdown2 = 178;
 XRup1 = 154;
 YRup1 = 120;
 XRdown1 = 194;
 YRdown1 = 1;
 YRup2 = 180;
 XRup2 = 194;
 XRdown2 = 154;
 YRdown2 = 60;
 //Total line reach = 180
 //Lines dont intersect yet
  for (;XLup2 <= 86 ;XLup1=XLup1+speed, XLdown1=XLdown1+speed,
    XLup2=XLup2+speed, XLdown2=XLdown2+speed, XRup1=XRup1-speed, XRdown1=XRdown1-
    speed, XRup2=XRup2-speed, XRdown2=XRdown2-speed) {
    upLine.drawLine(0, 0, 40, 60, TFT_BLACK);
    downLine.drawLine(40, 0, 0, 60, TFT_BLACK);

    upLine.pushSprite(XLup1, YLup1, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown1, YLdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XLup2, YLup2, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown2, YLdown2, TFT_TRANSPARENT);
    upLine.pushSprite(XRup1, YRup1, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown1, YRdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XRup2, YRup2, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown2, YRdown2, TFT_TRANSPARENT);
    upLine.drawLine(0, 0, 40, 60, OMNITRIX_GRAY);
    downLine.drawLine(40, 0, 0, 60, OMNITRIX_GRAY);
    upLine.pushSprite(XLup1 - BLACK_LINE_WIDTH, YLup1, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown1 - BLACK_LINE_WIDTH, YLdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XLup2 - BLACK_LINE_WIDTH, YLup2, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown2 - BLACK_LINE_WIDTH, YLdown2, TFT_TRANSPARENT);
    upLine.pushSprite(XRup1 + BLACK_LINE_WIDTH, YRup1, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown1 + BLACK_LINE_WIDTH, YRdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XRup2 + BLACK_LINE_WIDTH, YRup2, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown2 + BLACK_LINE_WIDTH, YRdown2, TFT_TRANSPARENT);
    }
    //Black lines intersect with each other up to the middle sprites (40,60)
    for (;XLup2 <= 126 ;XLup1=XLup1+speed, XLdown1=XLdown1+speed,
    XLup2=XLup2+speed, XLdown2=XLdown2+speed, XRup1=XRup1-speed, XRdown1=XRdown1-
    speed, XRup2=XRup2-speed, XRdown2=XRdown2-speed) {
    upLine.drawLine(0, 0, 40, 60, TFT_BLACK);
    downLine.drawLine(40, 0, 0, 60, TFT_BLACK);

    upLine.pushSprite(XLup1, YLup1, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown1, YLdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XLup2, YLup2, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown2, YLdown2, TFT_TRANSPARENT);
    upLine.pushSprite(XRup1, YRup1, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown1, YRdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XRup2, YRup2, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown2, YRdown2, TFT_TRANSPARENT);
    upLine.drawLine(0, 0, 40, 60, OMNITRIX_GRAY);
    downLine.drawLine(40, 0, 0, 60, OMNITRIX_GRAY);
    upLine.pushSprite(XLup1 - BLACK_LINE_WIDTH, YLup1, TFT_TRANSPARENT);
    //downLine.pushSprite(XLdown1 - BLACK_LINE_WIDTH, YLdown1,TFT_TRANSPARENT);
    //upLine.pushSprite(XLup2 - BLACK_LINE_WIDTH, YLup2, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown2 - BLACK_LINE_WIDTH, YLdown2, TFT_TRANSPARENT);
    //upLine.pushSprite(XRup1 + BLACK_LINE_WIDTH, YRup1, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown1 + BLACK_LINE_WIDTH, YRdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XRup2 + BLACK_LINE_WIDTH, YRup2, TFT_TRANSPARENT);
    //downLine.pushSprite(XRdown2 + BLACK_LINE_WIDTH, YRdown2,TFT_TRANSPARENT);
    upLine.drawLine(0, 0, 40, 60, OMNITRIX_GREEN);
    downLine.drawLine(40, 0, 0, 60, OMNITRIX_GREEN);
    //upLine.pushSprite(XLup1 - BLACK_LINE_WIDTH - 1, YLup1,TFT_TRANSPARENT);
    downLine.pushSprite(XLdown1 - BLACK_LINE_WIDTH - 1, YLdown1,TFT_TRANSPARENT);
    upLine.pushSprite(XLup2 - BLACK_LINE_WIDTH - 1, YLup2, TFT_TRANSPARENT);
    //downLine.pushSprite(XLdown2 - BLACK_LINE_WIDTH - 1, YLdown2,TFT_TRANSPARENT);
    upLine.pushSprite(XRup1 + BLACK_LINE_WIDTH + 1, YRup1, TFT_TRANSPARENT);
    //downLine.pushSprite(XRdown1 + BLACK_LINE_WIDTH + 1, YRdown1,TFT_TRANSPARENT);
    //upLine.pushSprite(XRup2 + BLACK_LINE_WIDTH + 1, YRup2,TFT_TRANSPARENT);
    downLine.pushSprite(XRdown2 + BLACK_LINE_WIDTH + 1, YRdown2, TFT_TRANSPARENT);
    upLine.drawLine(0, 0, 40, 60, OMNITRIX_GRAY);
    downLine.drawLine(40, 0, 0, 60, OMNITRIX_GRAY);

    //upLine.pushSprite(XLup1 - BLACK_LINE_WIDTH - 1, YLup1,TFT_TRANSPARENT);
    upLine.pushSprite(XLdown1 - BLACK_LINE_WIDTH - 1 - 40 , YLdown1 ,
    TFT_TRANSPARENT);
    downLine.pushSprite(XLup2 - BLACK_LINE_WIDTH - 1 - 40, YLup2 - 1,
    TFT_TRANSPARENT);
    //downLine.pushSprite(XLdown2 - BLACK_LINE_WIDTH - 1, YLdown2,TFT_TRANSPARENT);
    downLine.pushSprite(XRup1 + BLACK_LINE_WIDTH + 1 + 40, YRup1 ,
    TFT_TRANSPARENT);
    //downLine.pushSprite(XRdown1 + BLACK_LINE_WIDTH + 1, YRdown1,TFT_TRANSPARENT);
    //upLine.pushSprite(XRup2 + BLACK_LINE_WIDTH + 1, YRup2,TFT_TRANSPARENT);
    upLine.pushSprite(XRdown2 + BLACK_LINE_WIDTH + 1 + 40, YRdown2,
    TFT_TRANSPARENT);
 }

 //Black lines intersect with each other only to the upper sprites (40,60)
  for (;XLup2 <= 166 ;XLup1=XLup1+speed, XLdown1=XLdown1+speed,
    XLup2=XLup2+speed, XLdown2=XLdown2+speed, XRup1=XRup1-speed, XRdown1=XRdown1-
    speed, XRup2=XRup2-speed, XRdown2=XRdown2-speed) {
    upLine.drawLine(0, 0, 40, 60, TFT_BLACK);
    downLine.drawLine(40, 0, 0, 60, TFT_BLACK);

    upLine.pushSprite(XLup1, YLup1, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown1, YLdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XLup2, YLup2, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown2, YLdown2, TFT_TRANSPARENT);
    upLine.pushSprite(XRup1, YRup1, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown1, YRdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XRup2, YRup2, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown2, YRdown2, TFT_TRANSPARENT);
    upLine.drawLine(0, 0, 40, 60, OMNITRIX_GRAY);
    downLine.drawLine(40, 0, 0, 60, OMNITRIX_GRAY);
    upLine.pushSprite(XLup1 - BLACK_LINE_WIDTH, YLup1, TFT_TRANSPARENT);
    //downLine.pushSprite(XLdown1 - BLACK_LINE_WIDTH, YLdown1,TFT_TRANSPARENT);
    //upLine.pushSprite(XLup2 - BLACK_LINE_WIDTH, YLup2, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown2 - BLACK_LINE_WIDTH, YLdown2, TFT_TRANSPARENT);
    //upLine.pushSprite(XRup1 + BLACK_LINE_WIDTH, YRup1, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown1 + BLACK_LINE_WIDTH, YRdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XRup2 + BLACK_LINE_WIDTH, YRup2, TFT_TRANSPARENT);
    //downLine.pushSprite(XRdown2 + BLACK_LINE_WIDTH, YRdown2,TFT_TRANSPARENT);
    upLine.drawLine(0, 0, 40, 60, OMNITRIX_GREEN);
    downLine.drawLine(40, 0, 0, 60, OMNITRIX_GREEN);
    //upLine.pushSprite(XLup1 - BLACK_LINE_WIDTH - 1, YLup1,TFT_TRANSPARENT);
    downLine.pushSprite(XLdown1 - BLACK_LINE_WIDTH - 1, YLdown1,
    TFT_TRANSPARENT);
    upLine.pushSprite(XLup2 - BLACK_LINE_WIDTH - 1, YLup2, TFT_TRANSPARENT);
    //downLine.pushSprite(XLdown2 - BLACK_LINE_WIDTH - 1, YLdown2, TFT_TRANSPARENT);
    upLine.pushSprite(XRup1 + BLACK_LINE_WIDTH + 1, YRup1, TFT_TRANSPARENT);
    //downLine.pushSprite(XRdown1 + BLACK_LINE_WIDTH + 1, YRdown1,  TFT_TRANSPARENT);
    //upLine.pushSprite(XRup2 + BLACK_LINE_WIDTH + 1, YRup2, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown2 + BLACK_LINE_WIDTH + 1, YRdown2,
    TFT_TRANSPARENT);
  }
 //End of lines covering with gray, draw green
  for (;XLup2 <= 180 ;XLup1=XLup1+speed, XLdown1=XLdown1+speed,
    XLup2=XLup2+speed, XLdown2=XLdown2+speed, XRup1=XRup1-speed, XRdown1=XRdown1-
    speed, XRup2=XRup2-speed, XRdown2=XRdown2-speed) {
    upLine.drawLine(0, 0, 40, 60, TFT_BLACK);
    downLine.drawLine(40, 0, 0, 60, TFT_BLACK);

    upLine.pushSprite(XLup1, YLup1, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown1, YLdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XLup2, YLup2, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown2, YLdown2, TFT_TRANSPARENT);
    upLine.pushSprite(XRup1, YRup1, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown1, YRdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XRup2, YRup2, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown2, YRdown2, TFT_TRANSPARENT);
    upLine.drawLine(0, 0, 40, 60, OMNITRIX_GRAY);
    downLine.drawLine(40, 0, 0, 60, OMNITRIX_GRAY);
    upLine.pushSprite(XLup1 - BLACK_LINE_WIDTH, YLup1, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown1 - BLACK_LINE_WIDTH, YLdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XLup2 - BLACK_LINE_WIDTH, YLup2, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown2 - BLACK_LINE_WIDTH, YLdown2, TFT_TRANSPARENT);
    upLine.pushSprite(XRup1 + BLACK_LINE_WIDTH, YRup1, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown1 + BLACK_LINE_WIDTH, YRdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XRup2 + BLACK_LINE_WIDTH, YRup2, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown2 + BLACK_LINE_WIDTH, YRdown2, TFT_TRANSPARENT);
    upLine.drawLine(0, 0, 40, 60, OMNITRIX_GREEN);
    downLine.drawLine(40, 0, 0, 60, OMNITRIX_GREEN);
    upLine.pushSprite(XLup1 - BLACK_LINE_WIDTH - 1, YLup1, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown1 - BLACK_LINE_WIDTH - 1, YLdown1,
    TFT_TRANSPARENT);
    upLine.pushSprite(XLup2 - BLACK_LINE_WIDTH - 1, YLup2, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown2 - BLACK_LINE_WIDTH - 1, YLdown2,
    TFT_TRANSPARENT);
    upLine.pushSprite(XRup1 + BLACK_LINE_WIDTH + 1, YRup1, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown1 + BLACK_LINE_WIDTH + 1, YRdown1,
    TFT_TRANSPARENT);
    upLine.pushSprite(XRup2 + BLACK_LINE_WIDTH + 1, YRup2, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown2 + BLACK_LINE_WIDTH + 1, YRdown2,
    TFT_TRANSPARENT);
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

}

