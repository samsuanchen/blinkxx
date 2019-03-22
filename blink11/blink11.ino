/* blink11.ino
  Open Arduino IDE Serial Monitor, from input box we may try the following one by one:
  16 input                              ( Let the led off. 讓燈關閉 )
  4 output 4 high                       ( Let the screen back light on. 讓屏幕背光打開 )
  25 17 buzzerSetup buzzerOn 261.6 tone ( Let the buzzer hum C4 pitch. 讓蜂鳴器發 C4 音 )
  329.6 tone 1000 ms  440.0 tone        ( Let the buzzer hum E4 and A4 pitchs. 讓蜂鳴器多發 E4 與 A4 倆音 )
  0 tone                                ( Let the buzzer off. 讓蜂鳴器靜音 )
*/
int  led          =   16;
int  delayHIGH    = 1000;
int  delayLOW     = 1000;
int  timeToChange = delayLOW;
int levelToChange = HIGH;
#include <fvm.h>                                          // ##### 1.1. FVM class the Forth virtual machine
FVM F;                                                    // ##### 1.2. define F as an instence of FVM



void setup() {
  F.init( 115200 );                                       // ##### 3.1. in setup(), initialize F and the word set



  pinMode(led, OUTPUT);                                   // set led pin for output (pin level become LOW)
}
void loop() {
  if( millis() < timeToChange ) return;                   // do nothing before time to change
  digitalWrite( led, levelToChange );                     // change led pin level
  timeToChange += levelToChange ? delayHIGH : delayLOW;   // next time to change led pin level
  levelToChange = HIGH - levelToChange;                   // next led pin level to change
}
