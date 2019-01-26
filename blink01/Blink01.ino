/*
  Blink01 https://github.com/samsuanchen/blink01

  Turns an LED on for one second, then off for one second, repeatedly.
  Not using delay(), an alternative blink is given to run in the same feature of
  Arduino basic example Blink, http://www.arduino.cc/en/Tutorial/Blink.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  derived 9 Jan 2019 by samsuanchen@gmail.com
*/

// remember time and level to change led HIGH / LOW
int timeChangeLevel;
int changLevel;

// delay period
int periodHIGH = 1000;
int periodLOW = 1000;

#define LED_BUILTIN 16 // for WIFIBOY 32

// the setup function runs once when you press reset or power the board
void setup() {
  
  // set LED_BUILTIN as a digital output divice (pin level become LOW).
  pinMode(LED_BUILTIN, OUTPUT);

  // next time and level to change
  timeChangeLevel = periodLOW;
  changLevel = HIGH;
  
}

// the loop function runs over and over again forever
void loop() {

  // wait time to change
  if( millis() >= timeChangeLevel ) {

    // chang level
    digitalWrite( LED_BUILTIN, changLevel );

    // next time and level to change
    timeChangeLevel += changLevel ? periodHIGH : periodLOW;
    changLevel = changLevel ? LOW : HIGH;
    
  }
}
