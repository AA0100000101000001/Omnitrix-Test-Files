//Intersection of two lines for Omnitrix hard coded animation 

void setup() {

  Serial.begin(115200);

}

void loop() {
  
  /*float  sA1, sB1, sA2, sB2, sC1, sC2; // A1x + B1y = C1, A2x + B2y = C2

  sA1 = -1.0;
  sB1 = 1.0;
  sC1 = 0.0;
  sA2 = 1.0;
  sB2 = 1.0;
  sC2 = 240.0;*/

  //Finding equations for lines [(0,0),(240,240)] and [(0,240),(240,0)]
  //For [(0,0),(240,240)]:
  //slope(a) = (240-0)/(240-0) = 1
  //Finding b with point (0,0): y = ax + b => 0 = 1*0 + b => b = 0
  //y = x;
  //-1*x + 1*y = 0

  //For [(240,240),(0,0)]:
  //a = (0-240)/(240-0) = -1
  //y = ax + b => 0 = -1*240 + b => b = 240
  //y = -1*x + 240
  //1*x + 1*y = 240

  //Test Omnitrix animation line equations  
  float Ax1 = -6.0, Ay1 = 0.0, Ax2 = 74.0, Ay2 = 120.0; //first line points
  float Bx1 = 246.0, By1 = 0.0, Bx2 = 166.0, By2 = 120.0; //second line points
  float x = 0, y = 0; //x,y result

  //Lines are always intersecting because they have opposite slopes 
  //but the function will be called after x > 120 where the intersecting matters the most
  for( ; Ax2 <= 215 ; Ax1++, Ax2++, Bx1--, Bx2--) {
    //getCommonPoint(sA1, sB1, sC1, sA2, sB2, sC2, &x, &y);
    float d = getCommonPoint(Ax1, Ay1, Ax2, Ay2, Bx1, By1, Bx2, By2,  &x, &y);

    if (d == 0) {
      Serial.println("Lines are parallel");
    }
    else {
      Serial.println("Lines are intersecting");
    }

    Serial.print(" Common Point (x, y) = (");
    Serial.print(x);
    Serial.print(", ");
    Serial.print(y);
    Serial.println(")");

    delay(200);
  }

  delay(10000);

}

//void getCommonPoint(float sA1, float sB1, float sC1, float sA2, float sB2, float sC2, float* x, float* y) {
//Find common point of lines A[(Ax1, Ay1),(Ax2, Ay2)] and B[(Bx1, By1),(Bx2, By2)]
float getCommonPoint(float Ax1, float Ay1, float Ax2, float Ay2, float Bx1, float By1, float Bx2, float By2, float* x, float* y) {

  float dx, dy, Aa, Ba, Ab, Bb;

  //Find A's equation
  dx = Ax2 - Ax1;
  dy = Ay2 - Ay1;
  Aa = dy / dx; //slope a
  Ab = Ay1 - Aa*Ax1; //b = y1 - ax1
  //y = Aa*x + Ab
  
  //Find B's equation
  dx = Bx2 - Bx1;
  dy = By2 - By1;
  Ba = dy / dx; //slope a
  Bb = By1 - Ba*Bx1; //b = y1 - ax1
  //y = Ba*x + Bb
/*
  Serial.print("Aa = ");
  Serial.print(Aa);
  Serial.print(" Ba = ");
  Serial.print(Ab);
  Serial.println(" Ba = ");
  Serial.print(Ba);
  Serial.print(" Bb = ");
  Serial.println(Bb);
*/
  //float delta = sA1 * sB2 - sA2 * sB1; // A1x + B1y = C1, A2x + B2y = C2
  float delta = Aa * (-1) - Ba * (-1);

  //Serial.print("delta = ");
  //Serial.println(delta);

  if (delta == 0) {
    //Serial.println("Lines are parallel");
    *x = 0;
    *y = 0;
    return delta;
  }
  //else {
    //Serial.println("Lines are intersecting");
  //}

  //*x = (sB2 * sC1 - sB1 * sC2) / delta;
  //*y = (sA1 * sC2 - sA2 * sC1) / delta;
  *x = -((-1) * Ab - (-1) * Bb) / delta;
  *y = -(Aa * Bb - Ba * Ab) / delta;
  
  return delta;

}
