
//Start mode to Alien Selection mode
void mode1to2() {

  mode = 2;
	Serial.println("Button pressed, select alien");

  //Display animation
  showAnimation();
      
	delay(600);

  //Display alien
  ShowAlien();

}

//Alien Selection mode to Start mode
void mode2to1() {

  mode = 1;
  Serial.println("Button pressed, back to start");

  delay(300);

  //display start
  tft.fillScreen(OMNITRIX_GREEN);
  ShowSymbols();

}

//Alien Selection mode to Transformation mode
void mode2to3() {

  mode = 3;
  Serial.println("Tranformed into alien");

  //Display tranformation image
  tft.fillScreen(OMNITRIX_GREEN);
  delay(600);

  //Display transformed state image
  tft.fillScreen(TFT_WHITE);
  ShowSymbols();

  delay(200);

}

//Transformation mode to Recharging mode
void mode3to4() {
  
  //Display red screen
  tft.fillScreen(OMNITRIX_RED);
  ShowSymbols();

  Serial.println("Omnitrix is recharging");

  mode = 4;

}

//Transformation mode to Start mode
void mode3to1() {

  mode = 1;
  Serial.println("Button pressed, untransforming and going back to Start mode");

  //display start
  tft.fillScreen(OMNITRIX_GREEN);
  ShowSymbols();

}

//Rechargin mode to Start mode
void mode4to1() {

  //Display green screen
  tft.fillScreen(OMNITRIX_GREEN);
  ShowSymbols();

  Serial.println("Going back to start");
  
  mode = 1;

}