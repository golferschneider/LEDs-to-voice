*************************************************************************
* * Created by: Kyle Schneider on March 23rd, 2015
* _______________________
*
* This program is free software: you can redistribute it and/or modify it.
* This program is distributed in the hope that it will be useful but WITHOUT ANY WARRANTY!
*************************************************************************


// Defining for LEDs
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define topLeftPin 6
#define bottomLeftPin 3
#define topRightPin 5
#define bottomRightPin 9

Adafruit_NeoPixel TLstrip = Adafruit_NeoPixel(38, topLeftPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel BLstrip = Adafruit_NeoPixel(38, bottomLeftPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel TRstrip = Adafruit_NeoPixel(38, topRightPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel BRstrip = Adafruit_NeoPixel(38, bottomRightPin, NEO_GRB + NEO_KHZ800);

 // Define hardware connections
#define PIN_GATE_IN 2
#define IRQ_GATE_IN  0
#define PIN_LED_OUT 13
#define PIN_ANALOG_IN A0

// soundISR()
// This function is installed as an interrupt service routine for the pin
// change interrupt.  When digital input 2 changes state, this routine
// is called.
// It queries the state of that pin, and sets the onboard LED to reflect that 
// pin's state.
void soundISR()
{
  int pin_val;

  pin_val = digitalRead(PIN_GATE_IN);
  digitalWrite(PIN_LED_OUT, pin_val);   
}

void setup()
{
  Serial.begin(9600);

  //  Configure LED pin as output
  pinMode(PIN_LED_OUT, OUTPUT);

  // configure input to interrupt
  pinMode(PIN_GATE_IN, INPUT);
  attachInterrupt(IRQ_GATE_IN, soundISR, CHANGE);

  TRstrip.begin();
  TLstrip.begin();
  BLstrip.begin();
  BRstrip.begin();
  TRstrip.show(); // Initialize all pixels to 'off'
  TLstrip.show();
  BRstrip.show();
  BLstrip.show();

  
  // Display status
  Serial.println("Initialized");
}

void loop()
{
  double value;
  //below is the volume constant, messing with different volume constants will allow more or less LEDs to show at the same input volume
  double constant = 7; 
  
  // Check the envelope input from the audio sensor
  value = analogRead(PIN_ANALOG_IN);
  
 // Serial.println(value); //easy way to test what kind of values you are getting from the audio sensor
 //the largest that value can be is 'constant'
  if(value > constant)
    value = constant;
  double percentPinsToTurnOn = 1 - ((constant - value)/constant); //get percentage of volume input to max we are allowing (constant)
  int  pinsToTurnOn = 38 * percentPinsToTurnOn; //by multiplying the percent by 38 (num of LEDs in each strip) we get how many LEDs to turn on
  //Serial.println(pinsToTurnOn);
  
    //generates colors for the appropriate LEDs that should be turned on
    for(int i = 0; i < pinsToTurnOn; i++){
      int redColor = rcolor(i);
      int greenColor = gcolor(i);
      int blueColor = bcolor(i);
      TRstrip.setPixelColor(i, redColor, greenColor, blueColor);
      BLstrip.setPixelColor(i,  redColor, greenColor, blueColor);
      BRstrip.setPixelColor(i,  redColor, greenColor, blueColor);
      TLstrip.setPixelColor((36 - i),  redColor, greenColor, blueColor);
      TLstrip.show();
      TRstrip.show();
      BRstrip.show();
      BLstrip.show(); 
    }  
    
    //Turns off all LEDs that should not be on
    for(int i = pinsToTurnOn; i < 38; i++){
      TRstrip.setPixelColor(i,0,0,0);
      BLstrip.setPixelColor(i,0,0,0);
      BRstrip.setPixelColor(i,0,0,0);
      TLstrip.setPixelColor((38 - i), 0,0,0);
      TLstrip.show();
      TRstrip.show();
      BRstrip.show();
      BLstrip.show(); 
    }
  // pause for .1 second
  delay(100);
}
double brightnessConstant = .35; //mess with this to get different hues of color
//I had LED diodes 1-10 be a form of red color, as you can see each diode is different from the last
int rcolor(double i){
  if(i == 0){
    return 0 * brightnessConstant;
  }else if(i == 1){
    return 5 * 1* brightnessConstant;
  }else if(i == 2){
    return 5 * 2* brightnessConstant;
  }else if(i == 3){
    return 5 * 3* brightnessConstant;
  }else if(i == 4){
    return 5 * 4* brightnessConstant;
  }else if(i == 5){
    return 5 * 5* brightnessConstant;
  }else if(i == 6){
    return 5 * 6* brightnessConstant;
  }else if(i == 7){
    return 5 * 7* brightnessConstant;
  }else if(i == 8){
    return 5 * 8* brightnessConstant;
  }else if(i == 9){
    return 5 * 9* brightnessConstant;
  }else if(i == 10){
    return 5 * 10* brightnessConstant;
  }else
  if(i < 38){
    return 50* brightnessConstant; 
  }
}

//I had pins 11-38 have some aspect of green in them
int gcolor(double i){
  if(i < 11){
    return 0* brightnessConstant; 
  }else if(i == 11){
    return 3.25* brightnessConstant; 
  }else if(i == 12){
    return 3.25 * 2* brightnessConstant; 
  }else if(i == 13){
    return 3.25 * 3* brightnessConstant; 
  }else if(i == 14){
    return 3.25 * 4* brightnessConstant; 
  }else if(i == 15){
    return 3.25 * 5* brightnessConstant; 
  }else if(i == 16){
    return 3.25 * 6* brightnessConstant; 
  }else if(i == 17){
    return 3.25 * 7* brightnessConstant; 
  }else if(i == 18){
    return 3.25 * 8* brightnessConstant; 
  }else if(i == 19){
    return 3.25 * 9* brightnessConstant; 
  }else if(i == 20){
    return 3.25 * 10* brightnessConstant; 
  }else if(i == 21){
    return (3.25 *10* brightnessConstant) + 1.76 * 1* brightnessConstant;
  }else if(i == 22){
    return (3.25 *10* brightnessConstant) + 1.76 * 2* brightnessConstant;
  }else if(i == 23){
    return (3.25 *10* brightnessConstant) + 1.76 * 3* brightnessConstant;
  }else if(i == 24){
    return (3.25 *10* brightnessConstant) + 1.76 * 4* brightnessConstant;
  }else if(i == 25){
    return (3.25 *10* brightnessConstant) + 1.76 * 5* brightnessConstant;
  }else if(i == 26){
    return (3.25 *10* brightnessConstant) + 1.76 * 6* brightnessConstant;
  }else if(i == 27){
    return (3.25 *10* brightnessConstant) + 1.76 * 7* brightnessConstant;
  }else if(i == 28){
    return (3.25 *10* brightnessConstant) + 1.76 * 8* brightnessConstant;
  }else if(i == 29){
    return (3.25 *10* brightnessConstant) + 1.76 * 9* brightnessConstant;
  }else if(i == 30){
    return (3.25 *10* brightnessConstant) + 1.76 * 10* brightnessConstant;
  }else if(i == 31){
    return ((3.25 *10* brightnessConstant) + 1.76 * 10* brightnessConstant) - 1.3 * 1* brightnessConstant;
  }else if(i == 32){
    return ((3.25 *10* brightnessConstant) + 1.76 * 10* brightnessConstant) - 1.3 * 2* brightnessConstant;
  }else if(i == 33){
    return ((3.25 *10* brightnessConstant) + 1.76 * 10* brightnessConstant) - 1.3 * 3* brightnessConstant;
  }else if(i == 34){
    return ((3.25 *10* brightnessConstant) + 1.76 * 10* brightnessConstant) - 1.3 * 4* brightnessConstant;
  }else if(i == 35){
    return ((3.25 *10* brightnessConstant) + 1.76 * 10* brightnessConstant) - 1.3 * 5* brightnessConstant;
  }else if(i == 36){
    return ((3.25 *10* brightnessConstant) + 1.76 * 10* brightnessConstant) - 1.3 * 6* brightnessConstant;
  }else if(i == 37){
    return ((3.25 *10* brightnessConstant) + 1.76 * 10* brightnessConstant) - 1.3 * 7* brightnessConstant;
  }else if(i == 38){
    return ((3.25 *10* brightnessConstant) + 1.76 * 10* brightnessConstant) - 1.3 * 8* brightnessConstant;
  }
}

//I had LED diods 1-10 and 31-38 have blue in them
int bcolor(double i){
  if(i == 0){
    return 50* brightnessConstant;
  }else if(i == 1){
    return (50 - 5 * 1)* brightnessConstant;
  }else if(i == 2){
    return (50 - 5 * 2)* brightnessConstant;
  }else if(i == 3){
    return (50 - 5 * 3)* brightnessConstant;
  }else if(i == 4){
    return (50 - 5 * 4)* brightnessConstant;
  }else if(i == 5){
    return (50 - 5 * 5)* brightnessConstant;
  }else if(i == 6){
    return (50 - 5 * 6)* brightnessConstant;
  }else if(i == 7){
    return (50 - 5 * 7)* brightnessConstant;
  }else if(i == 8){
    return (50 - 5 * 8)* brightnessConstant;
  }else if(i == 9){
    return (50 - 5 * 9)* brightnessConstant;
  }else if(i == 10){
    return (50 - 5 * 10)* brightnessConstant;
  }else if(i < 30){
    return 0* brightnessConstant;
  }else if(i == 31){
    return 4.2 * 1* brightnessConstant;
  }else if(i == 32){
    return 4.2 * 2* brightnessConstant;
  }else if(i == 33){
    return 4.2 * 3* brightnessConstant;
  }else if(i == 34){
    return 4.2 * 4* brightnessConstant;
  }else if(i == 35){
    return 4.2 * 5* brightnessConstant;
  }else if(i == 36){
    return 4.2 * 6* brightnessConstant;
  }else if(i == 37){
    return 4.2 * 7* brightnessConstant;
  }else if(i == 38){
    return 4.2 * 8* brightnessConstant;
  }
}

