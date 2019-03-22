/* blink13.ino
  Open Arduino IDE Serial Monitor, from input box we may try the following one by one:
  50 setDelayLOW      ( Let the led become short flash per second. 讓燈每秒短暫閃亮 )
  50 setDelayHIGH     ( Let the led become flash quickly. 讓燈快速閃亮 )
  25 setLed 25 output ( Let the buzzer hum. 讓蜂鳴器滴答作響 )
  25 input            ( Let the buzzer off. 讓蜂鳴器關閉 )
*/
int  led          =   16;
int  periodHIGH   = 1000;
int  periodLOW    = 1000;
int levelToChange = HIGH;
int  timeToChange = periodHIGH;
#include <fvm.h>                                          // ##### 1.1. FVM class the Forth virtual machine
FVM F;                                                    // ##### 1.2. define F as an instence of FVM
void setDelayHIGH() { periodHIGH=F.dPop(); }              // ##### 2.1. define new function setDelayHIGH
void setDelayLOW()  { periodLOW =F.dPop(); }              // ##### 2.2. define new function setDelayLOW
void setLed()       { led       =F.dPop(); }              // ##### 2.3. define new function setLed
void setup() {
  F.init( 115200 );                                       // ##### 3.1. in setup(), initialize F and the word set
  F.newPrimitive( "\x0d" "setDelayHIGH", setDelayHIGH );  // ##### 4.1. add new primitive word setDelayHIGH in F
  F.newPrimitive( "\x0c" "setDelayLOW" , setDelayLOW  );  // ##### 4.2. add new primitive word setDelayLOW  in F
  F.newPrimitive( "\x05" "setLed"      , setLed       );  // ##### 4.3. add new primitive word getMillis    in F
  pinMode(led, OUTPUT);                                   // set led pin for output (pin level become LOW)
}
void loop() {
  if( millis() < timeToChange ) return;                   // do nothing before time to change
  digitalWrite( led, levelToChange );                     // change led pin level
  timeToChange += levelToChange ? periodHIGH : periodLOW; // next time to change led pin level
  levelToChange = HIGH - levelToChange;                   // next led pin level to change
}
