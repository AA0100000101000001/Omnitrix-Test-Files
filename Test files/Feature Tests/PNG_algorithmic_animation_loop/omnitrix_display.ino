#if defined START_ANIMATION_WITH_IMAGES
#define OMNITRIX_ANIM_FRAME_LAST_INDEX 10 //11 frames for animation
#elif defined START_ANIMATION_HARD_CODED
#define OMNITRIX_ANIM_FRAME_LAST (ANIM_TRIANGLE_PIXELS_TRAVEL-ANIM_TRIANGLE_WIDTH)
#endif

// Display position variables must be global for PNGdec
int16_t xpos = 0;
int16_t ypos = 0;



//Method that shows animation
//Returns true if finished, false if not done
bool show_animation() {

//Use of images for start animation
#if defined START_ANIMATION_WITH_IMAGES
  
  //Animation frames not done
  if (g_current_frame <= OMNITRIX_ANIM_FRAME_LAST_INDEX) {

    uint32_t next_frame = g_anim_start + ((g_current_frame+1) * FRAME_RATE);

#if defined ENABLE_ANIM_INFO
    Serial.printf("millis: %d, next frame at: %d\n", get_anim_time(), next_frame);
#endif

#if defined ENABLE_VERBOSE_ANIM_INFO
    unsigned long start_frame_time, start_frame_decod_time, frame_decod_duration_time, frame_duration_time, frame_duration_since_start;
#endif

    verbose_anim_info_save_anim_time(&start_frame_time);

    //Check time for next frame
    // g_anim_start + ((g_current_frame+1) * FRAME_RATE) is the next timestamp where the next frame appears
    if (get_anim_time() >= next_frame) {

      verbose_anim_info_save_anim_time(&start_frame_decod_time);

      //Draw current frame
      draw_start_animation_frame(g_current_frame);

      verbose_anim_info_end_frame(&start_frame_time, &frame_duration_time, &frame_duration_since_start, &frame_decod_duration_time, &start_frame_decod_time);

      g_current_frame++; //go to next frame

    }

  }
  // Animation frames finished
  else {

    //Finished animation info
    verbose_anim_end_info();

    return true; //Animation done
  }
  
  return false; //Animation not done



#elif defined START_ANIMATION_HARD_CODED
  
  int16_t xLup, xLmid, xLdown, xRup, xRmid, xRdown;
  uint8_t delay_time = 4;

  xLup = ANIM_TRIANGLE_BASE_OFFSET;
  xLmid = ANIM_TRIANGLE_WIDTH;
  xLdown = ANIM_TRIANGLE_BASE_OFFSET;
  xRup = TFT_WIDTH_USED - ANIM_TRIANGLE_BASE_OFFSET;
  xRmid = TFT_WIDTH_USED - ANIM_TRIANGLE_WIDTH;
  xRdown = TFT_WIDTH_USED - ANIM_TRIANGLE_BASE_OFFSET;

  //g_current_frame = 

  for (; (xLmid + BLACK_LINE_WIDTH) <= ANIM_TRIANGLE_PIXELS_TRAVEL; ) {

#if defined ENABLE_VERBOSE_ANIM_INFO
    unsigned long  start_frame_time, frame_duration_time, frame_duration_since_start;
#endif

      //Draw symbols up until they don't intersect yet
    if ((xLmid + BLACK_LINE_WIDTH) <= TFT_WIDTH_MIDDLE) {

      tft.startWrite();
      
      verbose_anim_info_save_anim_time(&start_frame_time);

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

      verbose_anim_info_end_frame(&start_frame_time, &frame_duration_time, &frame_duration_since_start);
      tft.endWrite();

    }
    //Black lines intersect with each other until their middle
    else if ((xLmid + BLACK_LINE_WIDTH) <= (TFT_WIDTH_MIDDLE + BLACK_LINE_WIDTH/2)) {

      int16_t comx, comy;
    
      //get common point of the lines: left up to mid gray part and right up to mid black part
      getCommonPoint(xLup, 0, xLmid, 120, xRup-BLACK_LINE_WIDTH, 0, xRmid-BLACK_LINE_WIDTH, 120, &comx, &comy);

      tft.startWrite();
      verbose_anim_info_save_anim_time(&start_frame_time);

      //Draw gray up lines
      tft.drawLine(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, OMNITRIX_GRAY); //Draw up left part
      tft.drawLine(xRup, 0, xRmid, TFT_HEIGHT_MIDDLE, OMNITRIX_GRAY); //Draw up right part
      //Draw black up lines
      tft.drawLine(xLup + BLACK_LINE_WIDTH, 0, xLmid + BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up left part
      tft.drawLine(xRup - BLACK_LINE_WIDTH, 0, xRmid - BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up right part
      
      //get common point of the lines: left mid to down gray part and right mid to down black part
      getCommonPoint(xLmid, 120, xLdown, 240, xRmid-BLACK_LINE_WIDTH, 120, xRdown-BLACK_LINE_WIDTH, 240, &comx, &comy);
      
      //Draw gray down lines
      tft.drawLine(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down left part
      tft.drawLine(xRmid, TFT_HEIGHT_MIDDLE, xRdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down right part
      //Draw black down lines
      tft.drawLine(xLmid + BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xLdown + BLACK_LINE_WIDTH, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down left part
      tft.drawLine(xRmid - BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xRdown - BLACK_LINE_WIDTH, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down right part

      verbose_anim_info_end_frame(&start_frame_time, &frame_duration_time, &frame_duration_since_start);
      tft.endWrite();
    }
    //Black lines intersect with each other until their end
    else if ((xLmid + BLACK_LINE_WIDTH) <= (TFT_WIDTH_MIDDLE + BLACK_LINE_WIDTH)) {

      int16_t comx, comy;

      //get common point of the lines: upper left to mid gray part and upper right to mid black part
      getCommonPoint(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, xRup-BLACK_LINE_WIDTH, 0, xRmid-BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, &comx, &comy);

      tft.startWrite();
      verbose_anim_info_save_anim_time(&start_frame_time);

      //Draw gray up lines
      tft.fillTriangle(xLup, 0, xLup-1, 0, comx, comy, OMNITRIX_GRAY); //Draw up left part with cleaning
      tft.fillTriangle(xRup, 0, xRup+1, 0, (TFT_WIDTH_USED-comx), comy, OMNITRIX_GRAY); //Draw up right part with cleaning
      //Draw black up lines
      tft.drawLine(xLup + BLACK_LINE_WIDTH, 0, xLmid + BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up left part
      tft.drawLine(xRup - BLACK_LINE_WIDTH, 0, xRmid - BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up right part
      
      //get common point of the lines: left mid to lower gray part and right mid to lower black part
      getCommonPoint(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, 
      xRmid-BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xRdown-BLACK_LINE_WIDTH, TFT_HEIGHT_USED, &comx, &comy);
      
      //Draw gray down lines
      tft.fillTriangle(comx, comy, xLdown-1, TFT_HEIGHT_USED, xLdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down left part with cleaning
      tft.fillTriangle((TFT_WIDTH_USED-comx), comy, xRdown+1, TFT_HEIGHT_USED, xRdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down right part with cleaning
      //Draw black down lines
      tft.drawLine(xLmid + BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xLdown + BLACK_LINE_WIDTH, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down left part
      tft.drawLine(xRmid - BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xRdown - BLACK_LINE_WIDTH, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down right part

      verbose_anim_info_end_frame(&start_frame_time, &frame_duration_time, &frame_duration_since_start);
      tft.endWrite();
    }
    //Gray triangle lines intersecting
    else if ((xLmid + BLACK_LINE_WIDTH) <= (TFT_WIDTH_MIDDLE + ANIM_TRIANGLE_START_LEFT_OFFSET + BLACK_LINE_WIDTH)) {

      int16_t comx, comy;
      
      //Clean the previous black line artifacts by covering them with green lines
      //Get common upper point of intersecting middle x lines
      getCommonPoint(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, xRup, 0, xRmid, TFT_HEIGHT_MIDDLE, &comx, &comy);

      //Serial.printf("comx: %d, comy: %d\n", comx, comy);

      tft.startWrite();
      verbose_anim_info_save_anim_time(&start_frame_time);

      //Draw green part of lines
      tft.fillTriangle(comx-1, comy, comx, comy, xLmid-1, TFT_HEIGHT_MIDDLE, OMNITRIX_GREEN); //Draw up left part with cleaning
      tft.fillTriangle(comx+1, comy, comx, comy, xRmid+1, TFT_HEIGHT_MIDDLE, OMNITRIX_GREEN); //Draw up right part with cleaning

      //This makes sure the upper right and left lines intersecting on the gray to black part have the right point
      //get common point of the lines: upper left to mid gray part and upper right to mid black part
      getCommonPoint(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, xRup-BLACK_LINE_WIDTH, 0, xRmid-BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, &comx, &comy);
      
      //Draw gray part of lines
      tft.fillTriangle(xLup-1, 0, xLup-2, 0, comx, comy, OMNITRIX_GRAY); //Draw up left partition with cleaning
      tft.fillTriangle(xRup+1, 0, xRup+2, 0, (TFT_WIDTH_USED-comx), comy, OMNITRIX_GRAY); //Draw up right part with cleaning purple 0x780F

      //Get common lower point of intersecting middle x lines
      getCommonPoint(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, 
      xRmid, TFT_HEIGHT_MIDDLE, xRdown, TFT_HEIGHT_USED, &comx, &comy);
      
      //Draw green part of lines
      tft.fillTriangle(xLmid-1, TFT_HEIGHT_MIDDLE, comx, comy, comx-1, comy, OMNITRIX_GREEN); //Draw down left part with cleaning
      tft.fillTriangle(xRmid+1, TFT_HEIGHT_MIDDLE, comx, comy, comx+1, comy, OMNITRIX_GREEN); //Draw down right part with cleaning

      //This makes sure the lower right and left lines intersecting on the gray to black part have the right point
      //get common point of the lines: left mid to lower gray part and right mid to lower black part
      getCommonPoint(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, 
      xRmid-BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xRdown-BLACK_LINE_WIDTH, TFT_HEIGHT_USED, &comx, &comy);

      //Draw gray part of lines
      tft.fillTriangle(comx, comy, xLdown-2, TFT_HEIGHT_USED, xLdown-1, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down left part with cleaning
      tft.fillTriangle((TFT_WIDTH_USED-comx), comy, xRdown+2, TFT_HEIGHT_USED, xRdown+1, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw down right part with cleaning

      //Draw black lines
      tft.drawLine(xLup + BLACK_LINE_WIDTH, 0, xLmid + BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up left part
      tft.drawLine(xRup - BLACK_LINE_WIDTH, 0, xRmid - BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up right part
      tft.drawLine(xLmid + BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xLdown + BLACK_LINE_WIDTH, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down left part
      tft.drawLine(xRmid - BLACK_LINE_WIDTH, TFT_HEIGHT_MIDDLE, xRdown - BLACK_LINE_WIDTH, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down right part

      verbose_anim_info_end_frame(&start_frame_time, &frame_duration_time, &frame_duration_since_start);
      tft.endWrite();
    }
    //Lines stop intersectiong 
    else {

      tft.startWrite();
      verbose_anim_info_save_anim_time(&start_frame_time);

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

      verbose_anim_info_end_frame(&start_frame_time, &frame_duration_time, &frame_duration_since_start);
      tft.endWrite();

#if defined ENABLE_VERBOSE_ANIM_INFO
      //Show points for last frame
      if ((xLmid + BLACK_LINE_WIDTH) == ANIM_TRIANGLE_PIXELS_TRAVEL) {
        Serial.printf("xLup: %d, xLmid: %d, xLdown: %d, xRup: %d, xRmid: %d, xRdown: %d\n", xLup, xLmid, xLdown, xRup, xRmid, xRdown);
      }
#endif
    }

#if defined ENABLE_VERBOSE_ANIM_INFO
    Serial.printf("Time passed since frame real time: %d micros, total time since start: %d micros\n", frame_duration_time, frame_duration_since_start);
#endif

    xLup++;
    xLmid++;
    xLdown++;
    xRup--;
    xRmid--;
    xRdown--;

  }

#if defined ENABLE_VERBOSE_ANIM_INFO
  Serial.printf("Average frame rate: %.2f micros\n", avrg_frame_time/OMNITRIX_ANIM_FRAME_LAST);
#endif
  

  return true;

#endif

}

//Gets curent time. Animation with images returns millis while hardcoded animation returns micros
unsigned long get_anim_time() {
#if defined START_ANIMATION_WITH_IMAGES
  return millis();
#elif defined START_ANIMATION_HARD_CODED
  return micros();
#endif
}

//Saves in the variable the current time
void verbose_anim_info_save_anim_time(unsigned long *start_frame_time) {
#if defined ENABLE_VERBOSE_ANIM_INFO
  *start_frame_time = get_anim_time();
#endif
}

//Saves in the variable frame_duration the difference from time now and a previous saved time
void verbose_anim_info_save_frame_time_diff(unsigned long* frame_duration, unsigned long* start_time) {
  *frame_duration = get_anim_time() - *start_time;
}

//Saves frame_duration_time, frame_duration_since_start and does avrg_frame_time calculation
void verbose_anim_info_end_frame_wrapper(unsigned long *start_frame_time, unsigned long *frame_duration_time, unsigned long *frame_duration_since_start) {
#if defined ENABLE_VERBOSE_ANIM_INFO
  verbose_anim_info_save_frame_time_diff(frame_duration_time, start_frame_time);
  verbose_anim_info_save_frame_time_diff(frame_duration_since_start, &g_anim_start);
  avrg_frame_time += (double) *frame_duration_time;
#endif
}

// Function verbose_anim_info_end_frame: prints info at the end of a frame
// Prints frame_duration_time, frame_duration_since_start and if animation with images is used also frame_decod_duration_time
#if defined START_ANIMATION_WITH_IMAGES
void verbose_anim_info_end_frame(unsigned long *start_frame_time, unsigned long *frame_duration_time, unsigned long *frame_duration_since_start, 
unsigned long *frame_decod_duration_time, unsigned long *start_frame_decod_time) {
  verbose_anim_info_end_frame_wrapper(start_frame_time, frame_duration_time, frame_duration_since_start);
  verbose_anim_info_save_frame_time_diff(frame_decod_duration_time, start_frame_decod_time);
  avrg_frame_decod_time += *frame_decod_duration_time;
  Serial.printf("Time passed since frame decoded: %d, time passed since frame real time: %d, total time since start: %d\n", 
        frame_decod_duration_time, frame_duration_time, frame_duration_since_start);
}
#elif defined START_ANIMATION_HARD_CODED
void verbose_anim_info_end_frame(unsigned long *start_frame_time, unsigned long *frame_duration_time, unsigned long *frame_duration_since_start) {
  
  verbose_anim_info_end_frame_wrapper(start_frame_time, frame_duration_time, frame_duration_since_start);
}
#endif

// Function verbose_anim_end_info: prints info at the end of the animation
// Prints Average frame rate, Total start_animation time length and if animation with images is enabled Average frame decode time
#if defined START_ANIMATION_WITH_IMAGES
void verbose_anim_end_info() {
#if defined ENABLE_VERBOSE_ANIM_INFO
    //Serial.println("HEREEEEE");
    end_animation_time = get_anim_time();
    Serial.printf("Average frame rate: %.2f, Average frame decode time: %.2f\n", 
      avrg_frame_time/(OMNITRIX_ANIM_FRAME_LAST_INDEX + 1), 
      avrg_frame_decod_time/(OMNITRIX_ANIM_FRAME_LAST_INDEX + 1));
    Serial.printf("Total start_animation time length : %d\n", end_animation_time - g_anim_start);
#endif
}
#elif defined START_ANIMATION_HARD_CODED
void verbose_anim_end_info() {

}
#endif



// Helper function for show_animation
void draw_start_animation_frame(uint8_t i) {

//Use of images for start animation
#if defined START_ANIMATION_WITH_IMAGES
  
  show_image(omnitrix_anim[i], sizeof(omnitrix_anim[i]));
#endif
}

//Method that shows the symbols for select mode
void show_select_symbols() {

  #if defined START_ANIMATION_WITH_IMAGES

  //Select Symbols with image
  show_image(omnitrix_anim[10], sizeof(omnitrix_anim[10]));

  //Hard coded start symbols
  #elif defined START_ANIMATION_HARD_CODED

  int16_t xLup, xLmid, xLdown, xRup, xRmid, xRdown, xLupEnd, black;

  xLupEnd = (TFT_WIDTH_MIDDLE-(ANIM_END_WIDTH_OFFSET/2)-BLACK_LINE_WIDTH-1);

  xLup = xLupEnd;
  xLmid = -ANIM_TRIANGLE_START_LEFT_OFFSET + xLupEnd;
  xLdown = xLupEnd; 
  xRup = TFT_WIDTH_USED - xLupEnd; 
  xRmid = ANIM_TRIANGLE_START_RIGHT_OFFSET - xLupEnd;
  xRdown = TFT_WIDTH_USED - xLupEnd;

  tft.fillTriangle(0, 0, xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, OMNITRIX_GRAY); //Draw left up gray part
  tft.fillTriangle(0, 0, xLmid, TFT_HEIGHT_MIDDLE, 0, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw left mid gray part
  tft.fillTriangle(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, 0, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw left down gray part
  tft.fillTriangle(xRup, 0, xRmid, TFT_HEIGHT_MIDDLE, TFT_WIDTH_USED, 0, OMNITRIX_GRAY); //Draw right up gray part
  tft.fillTriangle(TFT_WIDTH_USED, 0, xRmid, TFT_HEIGHT_MIDDLE, TFT_WIDTH_USED, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw right mid gray part
  tft.fillTriangle(xRmid, TFT_HEIGHT_MIDDLE, xRdown, TFT_HEIGHT_USED, TFT_WIDTH_USED, TFT_HEIGHT_USED, OMNITRIX_GRAY); //Draw right down gray part

  //Draw black lines
  for (black = 0; black <= BLACK_LINE_WIDTH; black++, xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown--) {
    tft.drawLine(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up left part
    tft.drawLine(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down left part
    tft.drawLine(xRup, 0, xRmid, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up right part
    tft.drawLine(xRmid, TFT_HEIGHT_MIDDLE, xRdown, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down right part
  }

  #endif

}

//Function that displays start icon symbols
void show_symbols() {

  #if defined START_ANIMATION_WITH_IMAGES

  //Start Symbols with image
  show_image(omnitrix_anim[0], sizeof(omnitrix_anim[0]));

  //Hard coded start symbols
  #elif defined START_ANIMATION_HARD_CODED

  int16_t xLup, xLmid, xLdown, xRup, xRmid, xRdown, black;

  xLup = -ANIM_TRIANGLE_START_LEFT_OFFSET + ANIM_TRIANGLE_WIDTH; 
  xLmid = ANIM_TRIANGLE_WIDTH; 
  xLdown = -ANIM_TRIANGLE_START_LEFT_OFFSET + ANIM_TRIANGLE_WIDTH;
  xRup = ANIM_TRIANGLE_START_RIGHT_OFFSET - ANIM_TRIANGLE_WIDTH; 
  xRmid = TFT_WIDTH_USED - ANIM_TRIANGLE_WIDTH; 
  xRdown = ANIM_TRIANGLE_START_RIGHT_OFFSET - ANIM_TRIANGLE_WIDTH;

  //Draw left gray triangle
  tft.fillTriangle(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, OMNITRIX_GRAY);
  //Draw right gray triangle
  tft.fillTriangle(xRup, 0, xRmid, TFT_HEIGHT_MIDDLE, xRdown, TFT_HEIGHT_USED, OMNITRIX_GRAY); 

  //Draw black lines
  for (black = 0; black <= BLACK_LINE_WIDTH; black++, xLup++, xLmid++, xLdown++, xRup--, xRmid--, xRdown--) {
    tft.drawLine(xLup, 0, xLmid, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up left part
    tft.drawLine(xLmid, TFT_HEIGHT_MIDDLE, xLdown, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down left part
    tft.drawLine(xRup, 0, xRmid, TFT_HEIGHT_MIDDLE, OMNITRIX_BLACK); //Draw up right part
    tft.drawLine(xRmid, TFT_HEIGHT_MIDDLE, xRdown, TFT_HEIGHT_USED, OMNITRIX_BLACK); //Draw down right part
  }

  #endif
}

//Function that displays alien on screen
// void show_alien() {

//   show_image(omnitrix_aliens[g_alien_n], sizeof(omnitrix_aliens[g_alien_n]));

// }

//Method that displays green backround to erase alien
// void erase_alien() {

//   show_image(omnitrix_alien_background, sizeof(omnitrix_alien_background));

// }

// This function displays png images
void show_image(const uint8_t *img, int img_size) {

#if defined ENABLE_MEMORY_INFO
  Serial.printf("Free Internal Heap: %d\n", ESP.getFreeHeap());
  Serial.printf("Min Free Internal Heap: %d\n", ESP.getMinFreeHeap());
  Serial.printf("Total PSRAM Size: %d\n", ESP.getPsramSize());
  Serial.printf("Free PSRAM: %d\n", ESP.getFreePsram());
#endif

  int16_t rc = png.openFLASH((uint8_t *)img, img_size, png_draw);

#if defined ENABLE_MEMORY_INFO
  Serial.printf("Open flash rc: %d\n", rc);
#endif

  if (rc == PNG_SUCCESS) {
#if defined ENABLE_MEMORY_INFO
    Serial.println("Successfully png file");
#endif

    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }

}

// This function will be called during decoding of the png file
int png_draw(PNGDRAW *pDraw) {
  uint16_t line_buffer[MAX_IMAGE_WDITH];         // Line buffer for rendering
  uint8_t mask_buffer[1 + MAX_IMAGE_WDITH / 8];  // Mask buffer

  png.getLineAsRGB565(pDraw, line_buffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);

  if (png.getAlphaMask(pDraw, mask_buffer, 255)) {
    tft.pushMaskedImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, line_buffer, mask_buffer);
  }

  return 1;
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
  Ba = (float) (By2 - By1)/ (Bx2 - Bx1);  //slope b
  Bb = (float) By1 - Ba*Bx1; //b = y1 - ax1
  //y = Ba*x + Bb

  //Find delta
  float delta = Aa * (-1) - Ba * (-1);

  //Check delta
  if (delta == 0) {
    *x = 0;
    *y = 0;
    return delta;
  }

  //Find common point
  fx = -((-1) * Ab - (-1) * Bb) / delta;
  fy = -(Aa * Bb - Ba * Ab) / delta;

  //Round to integer
  *x = (int16_t) fx;
  *y =(int16_t) fy;

  return delta;

}
#endif
