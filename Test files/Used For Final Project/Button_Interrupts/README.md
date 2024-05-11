# How to use 
 Connect four buttons in active high connection.  
# Tested with 
* Esp32-S2-DEV  
* Esp32-S3-Pico-DEV  
# Button States 
Mode 1 = Start Mode  
Mode 2 = Select Alien Mode  
Mode 3 = Transformation Mode  
|						|Mode 1	| Mode 2	| Mode 3	|
|-----------------------|-------|-----------|-----------|
|Start Button Pressed	|Mode 2	|Mode 1		|			|
|Right Button Pressed	|		|Mode 2		|			|
|Left Button Pressed	|		|Mode 2		|			|
|Select Button Pressed	|		|Mode 3		|Mode 1		|