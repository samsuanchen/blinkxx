/* blink01.ino
  Open Arduino IDE Serial Monitor, from input box we may try the following one by one:
  16 input                              ( Let the led off. 讓燈關閉 )
  25 17 buzzerSetup buzzerOn 261.6 tone ( Let the buzzer hum C4 pitch. 讓蜂鳴器發 C4 音 )
  329.6 tone 1000 ms  440.0 tone        ( Let the buzzer hum E4 and A4 pitchs. 讓蜂鳴器多發 E4 與 A4 倆音 )
  0 tone                                ( Let the buzzer off. 讓蜂鳴器靜音 )
  0 0 128 160 img wb_drawImage          ( Let the screen show picture. 讓屏幕顯示圖片 )
  27 output 27 low                      ( Let the screen back light on. 讓屏幕關閉 )
*/
#define LED_BUILTIN 16



#include <fvm.h>                                          // ##### 1.1. load FVM, the Forth virtual machine class
FVM F;                                                    // ##### 1.2. define F as an instence of FVM



void setup() { // the setup function runs once when you press reset or power the board
  F.init( 115200 );                                       // ##### 3.1. initialize F in setup function



  pinMode(LED_BUILTIN, OUTPUT);      // initialize digital pin LED_BUILTIN as output.
}
void loop() { // the loop function runs over and over again forever
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(  1000   );                  // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(  1000   );                  // wait for a second
}
