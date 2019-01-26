/*
  Blink02 https://github.com/samsuanchen/blink02

  Turns an LED on for one second, then off for one second, repeatedly.
  Not using delay(), an alternative blink is given to run in the same feature of
  Arduino basic example Blink, http://www.arduino.cc/en/Tutorial/Blink.
  More over, a virtual machine is includeded and activated so that
  while blinking we could do some thing else, for example to draw
  image, lines, and characters on wifiboy screen.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  derived from blink01, 5 lines added, 19 Jan 2019 by samsuanchen@gmail.com
*/

#include <fvm02.h>                                  // ##### 1.1. load FVM the Forth virtual machine
FVM F;                                              // ##### 1.2. define F as an instence of FVM

// remember time and level to change led HIGH / LOW
int timeChangeLevel;
int changLevel;

// delay period
int periodHIGH = 1000;
int periodLOW = 1000;

#define LED_BUILTIN 16 // for wifiboy 32

// the setup function runs once when you press reset or power the board
void setup() {

  extern Word* word_set;                            // ##### 3.1. load external word set (defined in fvm02_word_set.cpp)
  F.init( 115200, word_set );                       // ##### 3.2. in setup(), initialize F and the word set
  
  // set LED_BUILTIN as a digital output divice (pin level become LOW).
  pinMode(LED_BUILTIN, OUTPUT);

  // next time and level to change
  timeChangeLevel = periodLOW;
  changLevel = HIGH;
  
}

// the loop function runs over and over again forever
void loop() {
  
  F.update();                                       // ##### 5. in loop(), update F state

  // wait time to change
  if( millis() >= timeChangeLevel ) {

    // chang level
    digitalWrite( LED_BUILTIN, changLevel );

    // next time and level to change
    timeChangeLevel += changLevel ? periodHIGH : periodLOW;
    changLevel = changLevel ? LOW : HIGH;
    
  }

}
