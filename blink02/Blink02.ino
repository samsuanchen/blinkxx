/* blink02.ino
  Open Arduino IDE Serial Monitor, from input box we may try the following one by one:
  50 delayLOW  !      ( Let the led become short flash per second. 讓燈每秒短暫閃亮 )
  50 delayHIGH !      ( Let the led become flash quickly. 讓燈快速閃亮 )
  25 led ! 25 output 17 output 17 high ( Let the buzzer hum. 讓蜂鳴器滴答作響 )
  25 input            ( Let the buzzer off. 讓蜂鳴器關閉 )
  0 0 128 160 img wb_drawImage  1000 ms 27 output 27 low
*/
#define LED_BUILTIN 16
int  led          = LED_BUILTIN;
int  delayHIGH    = 1000;
int  delayLOW     = 1000;
#include <fvm.h>                                          // ##### 1.1. load FVM, the Forth virtual machine class
FVM F;                                                    // ##### 1.2. define F as an instence of FVM



void setup() { // the setup function runs once when you press reset or power the board
  F.init( 115200 );                                       // ##### 3.1. initialize F in setup function
  F.newVariable( "\x0d" "delayHIGH", &delayHIGH );        // ##### 4.1. add new primitive word setDelayHIGH in F
  F.newVariable( "\x0c" "delayLOW" , &delayLOW  );        // ##### 4.2. add new primitive word setDelayLOW  in F
  F.newVariable( "\x05" "led"      , &led       );        // ##### 4.3. add new primitive word getMillis    in F
  pinMode(led        , OUTPUT);      // initialize digital pin led         as output.
}
void loop() { // the loop function runs over and over again forever
  digitalWrite(led        , HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(delayHIGH);                  // wait for a second
  digitalWrite(led        , LOW);    // turn the LED off by making the voltage LOW
  delay(delayLOW );                  // wait for a second
}
