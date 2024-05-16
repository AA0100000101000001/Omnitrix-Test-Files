# Omnitrix-Test-Files  
 Tests of each of the Omnitrix features seperated into projects. This repository was created to test what the ESP32 can do. If someone wants to recreate the Omnitrix project they can start from here. These projects are also helpfull if someone wants to use a different board.  
   
 TFT-eSPI user setups are added in the Supported Displays folder that can be used in the LCD desplay tests.  
   
 The following projects are used in the Omnitrix currently:  
 * Button_Interrupts (GPIO interrupts test)  
 * PNG_animation_test (Animation test)  
 * Timer_With_Epoch_Time_Interrupts_Test (Deep sleep test with interrupts)  
 * Rotary_Encoder_Interrupts (Rotary Encoder with interrupts test)
 * dft_test (Sound test)  
 * config_test (Test for configuring settings and pins)

# To Do List:  
- [x] Use Micro switches instead of Encoder  
- [x] Power reduction code  
- [x] Make Schematic using EasyEDA  
- [x] Rewrite code to use GPIO interrupts  
- [x] Add config file for pin selection  
- [ ] Add support for ESP32-S3 Development Board   
- [ ] Use multiple inputs to wake up from deep sleep (ext1)  
- [ ] Power reduction code for LCD display   
- [ ] Check current consumption   
- [ ] Make PCB for ESP32-S3-LCD-1.28 1.27mm headers to 2.54mm   
- [ ] Find cheaper component for sound or use passive buzzer  
- [ ] Make rotary encoder mechanism  
- [ ] RGB LEDs  
- [ ] Only enable GPIO outputs (LEDs) at the last moment   
- [ ] Make PCB that has RGB LEDs, micro switches and speaker for ESP32-S3-LCD-1.28  
- [ ] Test LiPo battery with the board  
- [ ] Reduce size and memory usage of program sketch  
- [ ] Test operation when all Serial.println are removed  
- [ ] Create the rest of the mechanisms using a CAD program  
	
# Future Plans:  
- [ ] Add Default Demo mode   
- [ ] Create Omnitrix graphics for GC9A01 driver that uses library commands for animation  
- [ ] Make PCB for multiple RGB LEDs  
- [ ] Test current for LED PCB  
- [ ] Make PCB that has RGB LEDs, micro switches and speaker   
- [ ] GPIO pins as Vcc for inputs to reduce energy when in Deep Sleep  
- [ ] Add support for touch lcd  
- [ ] Add energy system  
- [ ] Secret combination input for Master Control Mode  
- [ ] Smoother animation  
- [ ] Xtra animation  
- [ ] Download aliens from a server  
- [ ] Update code with FOTA  
- [ ] Rechargable battery  
- [ ] Download additional aliens from a server  
- [ ] Add motor to elevate display (for fun!)  
- [ ] Make Omnitrix Microcontroller based on ESP32 chip  
- [ ] Add Menu that includes:  
* - [ ] Time  
* - [ ] Battery state  
* - [ ] Sound options  
* - [ ] Option to turn off LEDs  
* - [ ] Options for Changing tranformation Time variables  
* - [ ] Low power mode disable/enable (ULP coprossesor use in ESP-IDF)  
* - [ ] Demo Mode disable/enable  
* - [ ] Search for Updates  

