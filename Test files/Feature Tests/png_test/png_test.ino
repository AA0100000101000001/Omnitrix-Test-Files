
//Found in: Examples > TFT_eSPI > PNG > Flash_transparent_PNG

// This example renders a png file that is stored in a FLASH array
// using the PNGdec library (available via library manager).

// The example png is encoded as ARGB 8 bits per pixel with indexed colour
// It was created using GIMP and has a transparent background area.

// Image files can be converted to arrays using the tool here:
// https://notisrac.github.io/FileToCArray/
// To use this tool:
//   1. Drag and drop PNG image file on "Browse..." button
//   2. Tick box "Treat as binary"
//   3. Click "Convert"
//   4. Click "Save as file" and move the header file to sketch folder
//      (alternatively use the "Copy to clipboard" and paste into a new tab)
//   5. Open the sketch in IDE
//   6. Include the header file containing the array (SpongeBob.h in this example)

/* This program uses the PNGdec library to display the first twelve omnitrix aliens one after the other in a loop.

Tested with: 
ESP32-S2-DEV 
*/

// Include the PNG decoder library, available via the IDE library manager
#include <PNGdec.h>

// Include image array
#include "omnitrix_aliens.h"
#include "omnitrix_alien_backround.h"

PNG png; // PNG decoder instance

#define MAX_IMAGE_WDITH 240 // Sets rendering line buffer lengths, adjust for your images

#define OMNITRIX_GREEN 0xA707
#define OMNITRIX_RED 0xC000
#define OMNITRIX_GRAY 0xAD55

// Include the TFT library - see https://github.com/Bodmer/TFT_eSPI for library information
#include "SPI.h"
#include <TFT_eSPI.h>              // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();         // Invoke custom library

// Position variables must be global (PNGdec does not handle position coordinates)
int16_t xpos = 0;
int16_t ypos = 0;

//Number of aliens
int N = 11;
int Npos = 0;

//====================================================================================
//                                    Setup
//====================================================================================
void setup()
{
  Serial.begin(115200);
  Serial.println("\n\n Using the PNGdec library");

  // Initialise the TFT
  tft.begin();
  tft.fillScreen(OMNITRIX_GRAY);

  Serial.println("\r\nInitialisation done.");

}

//====================================================================================
//                                    Loop
//====================================================================================
void loop()
{

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
  
  delay(1000);

  if ((Npos + 1) > N ) {
    Npos = 0;
    }
  else {
    Npos += 1;
  }

  //tft.fillScreen(OMNITRIX_GRAY);

  int16_t rc2 = png.openFLASH((uint8_t *)omnitrix_alien_backround, sizeof(omnitrix_alien_backround), pngDraw);

  if (rc2 == PNG_SUCCESS) {
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

