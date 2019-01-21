# 為 簡單的 Arduino Blink 範例 加上 夢幻後門

我們提供 一系列 簡單的 blink 範例, 在 esp32 的 WiFiBoy 開發板上, 逐步使 blink 範例 加上 後門, 展現夢幻效果。

我們所謂 後門, 就是要在 Arduino 程式中, 啟動 我們提供的 FVM 虛擬機 (virtual machine)。 在程式執行的同時, 這虛擬機 可接受指令, 進行一些 額外工作,
或 直接改變 程式的 執行狀態和效果。

我們提供的 一系列 blink 範例 及 FVM 虛擬機, 包括: blink00, blink01, blink02, blink03, fvm02。


## blink00

在原 Arduino Blink 範例中, 多加一行 如下 #define 指令 讓程式 正常運行, 持續閃 led 亮 1 秒 滅 1 秒 亮 1 秒 滅 1 秒 ...。

    #define LED_BUILTIN 16 // for WIFIBOY 32


## blink01

改寫 Blink00 程式, 在 loop() 子程式中, 不用 delay(1000) 來維持 亮/滅 1 秒, 改用 millis() 來檢視時間, 直到過了 1 秒 才改變 亮/滅 並 設定下一個檢視時間。 這樣的設計 可讓我們有機會 善用 1 秒 的等待時間 去做些別的事。

 
## blink02

在原 blink01 程式中, setup() 前, 加 2 行 如下 指令, 讓程式 載入 FVM 虛擬機:

    #include <fvm02.h>                                // ##### 1.1. load FVM the Forth virtual machine
    FVM F;                                            // ##### 1.2. define F as an instence of FVM


setup() 中, 多加 2 行 如下 指令, 讓程式 啟動 FVM 虛擬機:

    extern Word* word_set;                            // ##### 3.1. load external word set (defined in fvm02_word_set.cpp)
    F.init( 115200, word_set );                       // ##### 3.2. in setup(), initialize F and the word set


loop() 中, 多加 1 行 如下 指令, 讓程式 更新 FVM 虛擬機 狀態:

    F.update();                                       // ##### 5. in loop(), update F state


一旦 啟動 FVM 虛擬機, 在 閃 led 的同時, 我們可試將 test.txt 中的 虛擬機 範例指令 貼到 Arduino IDE 的 Serial Monitor Console Input 輸入格, 讓 虛擬機 畫圖寫字。


## blink03

在原 blink02 程式中, setup() 前, 定義 3 個 Arduino functions, 以設定 led 亮/滅 時間, 以取得 當前時間。

    void setPeriodHIGH() { periodHIGH=F.dPop(); }       // ##### 2.1. define the function setPeriodHIGH
    void setPeriodLOW()  { periodLOW =F.dPop(); }       // ##### 2.2. define the function setPeriodLOW
    void getMillis() { F.dPush( millis() ); }           // ##### 2.3. define the function getMillis


setup() 中, 定義 3 個 虛擬機指令, 以分別執行 對應的 Arduino function。

   F.newPrimitive( "setPeriodHIGH", setPeriodHIGH ); // ##### 4.1. add new primitive word setPeriodHIGH in F
   F.newPrimitive( "setPeriodLOW",  setPeriodLOW  ); // ##### 4.2. add new primitive word setPeriodLOW  in F
   F.newPrimitive( "getMillis"   ,  getMillis     ); // ##### 4.3. add new primitive word getMillis     in F
  

一旦 啟動 FVM 虛擬機, 在 閃 led 的同時, 我們可試將 test.txt 中的 虛擬機 範例指令 貼到 Arduino IDE 的
Serial Monitor Console Input 輸入格, 讓 虛擬機 畫圖寫字 並且在 Console Output 顯示 畫圖寫字 所耗時間。
