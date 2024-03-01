
//Based on ESP32Time Library by Felix Biego

//This is a Test for RTC timer. It counts the time passed in seconds from the start of the program. 
//RTC Timer use is crucial in this project because it does not reset in deep sleep mode.
// Tested with 
// ESP32-S2-DEV  

#ifdef RTC_DATA_ATTR
RTC_DATA_ATTR static bool overflow;
#else
static bool overflow;
#endif

uint32_t startTime;
uint32_t timePassed;

void RTCsetTime(int sc, int mn, int hr, int dy, int mt, int yr, int ms) {
  // seconds, minute, hour, day, month, year $ microseconds(optional)
  // ie setTime(20, 34, 8, 1, 4, 2021) = 8:34:20 1/4/2021
  struct tm t = {0, 0, 0, 0, 0, 0, 0, 0, 0};      // Initalize to all 0's
  t.tm_year = yr - 1900;    // This is year-1900, so 121 = 2021
  t.tm_mon = mt - 1;
  t.tm_mday = dy;
  t.tm_hour = hr;
  t.tm_min = mn;
  t.tm_sec = sc;
  time_t timeSinceEpoch = mktime(&t);
  setTime(timeSinceEpoch, ms);
}

void setTime(unsigned long epoch, int ms) {
  struct timeval tv;
  if (epoch > 2082758399){
	  overflow = true;
	  tv.tv_sec = epoch - 2082758399;  // epoch time (seconds)
  } else {
	  overflow = false;
	  tv.tv_sec = epoch;  // epoch time (seconds)
  }
  tv.tv_usec = ms;    // microseconds
  settimeofday(&tv, NULL);
}

unsigned long RTCgetLocalEpoch() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	unsigned long epoch = tv.tv_sec;
	if (overflow){
		epoch += 63071999 + 2019686400;
	}
	return epoch;
}

void setup() {
  
  Serial.begin(115200);
  //Set Epoch Time
  RTCsetTime(0, 0, 0, 1, 1, 2023, 0);  // 1st Jan 2023 00:00:00
  //Get Epoch Time
  startTime = RTCgetLocalEpoch();

}

void loop() {
  
  //Wait 1 second
  delay(1000);
  //Get Epoch Time
  timePassed = RTCgetLocalEpoch();
  Serial.print("Seconds passed since start:");
  Serial.println(timePassed - startTime);

}
