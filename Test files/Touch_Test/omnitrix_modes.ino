
//Switch statement for start button modes
void startButtonModes() {

  switch (mode) {
    //Omnitrix is in start mode
    case 1:
      //Go to select alien mode
		  mode = 2;
      Serial.println("Mode 2");

      break;

    //Omnitrix is in select alien mode
    case 2:
      //Go to start mode
      mode = 1;
      Serial.println("Mode 1");

      break;
  }

}

//Switch statement for right button modes
void rightButtonModes() {

  switch (mode) {
    //Omnitrix is in select alien mode
    case 2:
      //If the next alien number is bigger than the total number of aliens
      //then go back to first alien, else go to the next alien
      if ((alienNo  + 1)> ALIEN_NUMBER ) {
        alienNo = 0;
      }
      else {
        alienNo += 1;
      }

      Serial.print("Right, alien no:");
      Serial.println(alienNo);
      delay(200);
      break;
  }

}

//Switch statement for left button modes
void leftButtonModes() {

  switch (mode) {
    //Omnitrix is in select alien mode
    case 2:
      //If the next alien number is less than 0
      //then go back to the last alien, else go to the previous alien
      if ((alienNo - 1) < 0 ) {
        alienNo = ALIEN_NUMBER;
      }
      else {
        alienNo -= 1;
      }

      Serial.print("Left, alien no:");
      Serial.println(alienNo);
      delay(200);
      break;
  }

}

//Switch statement for select button modes
void selectbuttonModes() {

  switch (mode) {
    //Omnitrix is in select alien mode
    case 2:
      //Go to transformation mode
		  mode = 3;
      Serial.println("Mode 3");

      break;

    //Omnitrix is in transformation mode
    case 3:
      //Go to Start mode
		  mode = 1;
      Serial.println("Mode 1");

      break;
  }

}
