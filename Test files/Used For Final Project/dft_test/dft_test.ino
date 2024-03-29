/*  This program is testing the DFRobot_DF1201S library with a ESP32. It uses a button as input to play three sounds. When the button is pressed then the first sound is played, 
when it is pressed again then the second sound is played and when it is pressed for the third time then the third sound is played. If the button is pressed again then the sequence
will repeat from the first sound.
    Serial ports are also tested for the ESP32S2 NODEMCU module.

	Tested with: 
	ESP32-S2-DEV  
*/

#include <DFRobot_DF1201S.h>
//#include <SoftwareSerial.h>

#define RXD1 18 //RX
#define TXD1 17 //TX
//SoftwareSerial DF1201SSerial(18, 17);  //RX  TX

const int buttonPin = 5;
int16_t sel = 9;

DFRobot_DF1201S DF1201S;
void setup(void){
  Serial.begin(115200);

  //Print serial pins:
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));
  
  pinMode(buttonPin, INPUT);

  //Print serial1 pins:
  Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1); //This is where the problem is, investigating with log_i, log_v(" %d ",..)
  Serial.println("Serial1 Txd1 is on pin: "+String(TXD1));
  Serial.println("Serial1 Rxd1 is on pin: "+String(RXD1));

  //Flush serial1
  //Serial1.flush();

  if (!Serial1) {
    Serial.println("No serial1"); //This doesn't print so serial1 is fine
  }

  int serial_read = Serial1.read();
  Serial.print("serial_read = ");
  Serial.println(serial_read);

  //check serial1 availability
  if (Serial1.available()) {
    Serial.println("available");
  } else {
    Serial.println("not available"); //But it's not available! 
  }                                  //It seems that in arduino-esp32/blob/master/cores/esp32/esp32-hal-uart
                                     //function uartAvailable: uart->has_peek returns false

  //Init DF1201S
  while(!DF1201S.begin(Serial1)){
    Serial.println("Init failed, please check the wire connection!");
    Serial.println(Serial1.peek());
    delay(4000);
  }
  DF1201S.setPrompt(true); //starting tone
  DF1201S.setLED(true); //led on
  /*Wait for the end of the prompt tone */
  delay(2000);
  /*Set playback mode to "repeat all"*/
  DF1201S.setPlayMode(DF1201S.SINGLE);
  /*Set volume to 10*/
  DF1201S.setVol(/*VOL = */10);
  Serial.print("VOL:");
  /*Get volume*/
  Serial.println(DF1201S.getVol());
  /*Enter music mode*/
  DF1201S.switchFunction(DF1201S.MUSIC);

}

void loop(){


  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    delay(200);

    if (sel == 9) {
    
      DF1201S.playFileNum(9);
      Serial.println(sel);
      sel = 10;

    } else if (sel == 10) {

      DF1201S.playFileNum(10);
      Serial.println(sel);
      sel = 11;
    } else if (sel == 11) {

      DF1201S.playFileNum(11);
      Serial.println(sel);
      sel = 9;
    }

  }

}
