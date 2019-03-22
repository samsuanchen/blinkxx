/* blink10.ino
  這範例 改寫 blink00, 在 loop() 子程式中, 不用 delay() 來維持 亮/滅 時間,
  改以 millis() 檢視時間, 直到過了 指定時間 才改變 亮/滅 並
  設定下一個檢視時間。 這樣的設計 可讓我們有機會 善用 1 秒 的等待時間
  去做些別的事。
*/
int  led          =   16;
int  delayHIGH    = 1000;
int  delayLOW     = 1000;
int  timeToChange = delayLOW;
int levelToChange = HIGH;





void setup() {




  pinMode(led, OUTPUT);                                   // set led pin for output (pin level become LOW)
}
void loop() {
  if( millis() < timeToChange ) return;                   // do nothing before time to change
  digitalWrite( led, levelToChange );                     // change led pin level
  timeToChange += levelToChange ? delayHIGH : delayLOW;   // next time to change led pin level
  levelToChange = HIGH - levelToChange;                   // next led pin level to change
}
