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

1. 在原 blink01 程式中, setup() 前, 加 2 行 如下 指令, 讓程式 載入 FVM 虛擬機:

	#include <fvm02.h>                                // ##### 1.1. load FVM the Forth virtual machine
	FVM F;                                            // ##### 1.2. define F as an instence of FVM


2. setup() 中, 多加 2 行 如下 指令, 讓程式 啟動 FVM 虛擬機:

	extern Word* word_set;                            // ##### 3.1. load external word set (defined in fvm02_word_set.cpp)
	F.init( 115200, word_set );                       // ##### 3.2. in setup(), initialize F and the word set


3. loop() 中, 多加 1 行 如下 指令, 讓程式 更新 FVM 虛擬機 狀態:

	F.update();                                       // ##### 5. in loop(), update F state


一旦 啟動 FVM 虛擬機, 在 閃 led 的同時, 我們可試將 test.txt 中的 虛擬機 範例指令 貼到 Arduino IDE 的 Serial Monitor Console Input 輸入格, 讓 虛擬機 畫圖寫字。


## blink03

1. 在原 blink02 程式中, setup() 前, 定義 3 個 Arduino functions, 以設定 led 亮/滅 時間, 以取得 當前時間。

	void setPeriodHIGH() { periodHIGH=F.dPop(); }       // ##### 2.1. define the function setPeriodHIGH
	void setPeriodLOW()  { periodLOW =F.dPop(); }       // ##### 2.2. define the function setPeriodLOW
	void getMillis() { F.dPush( millis() ); }           // ##### 2.3. define the function getMillis


2. setup() 中, 定義 3 個 虛擬機指令, 以分別執行 對應的 Arduino function。

	F.newPrimitive( "setPeriodHIGH", setPeriodHIGH ); // ##### 4.1. add new primitive word setPeriodHIGH in F
	F.newPrimitive( "setPeriodLOW",  setPeriodLOW  ); // ##### 4.2. add new primitive word setPeriodLOW  in F
	F.newPrimitive( "getMillis"   ,  getMillis     ); // ##### 4.3. add new primitive word getMillis     in F
  

一旦 啟動 FVM 虛擬機, 在 閃 led 的同時, 我們可試將 test.txt 中的 虛擬機 範例指令 貼到 Arduino IDE 的
Serial Monitor Console Input 輸入格, 改變 閃滅速度, 畫圖寫字, 並且顯示 所耗時間。


## 相關準備

### 1. 為 Arduino IDE 安裝 esp32 選項

請參閱 https://wifiboy.club/category/9/wifiboy32-esp32 檢視「如何安裝 Arduino IDE for WiFiBoy32」


### 2. 從 github 取得 範例 blink00, blink01, blink02, blink03, fvm02, wifiboy

	git clone https://github.com/samsuanchen/blinkxx

### 3. 將 fvm02 及 wifiboy 加入 Arduino libraries

	將 fvm02 與 wifiboy 資料夾 加入 Arduino IDE 的 libraries

## FVM 虛擬機 功能

	FVM f
	f.init(baud)
	f.init(baud,wordSet)
	f.eval(script)
	f.newPrimitive(name,func)
	f.newConstant(name,number)
	f.newVariable(name,address)
	f.update()


## 虛擬機 test.txt 範例 引用的指令 簡要說明

	'			( <name> -- w )	find the word of given name
	-			( n1 n2 -- n1-n2 ) subtract n1 by n2
	!			( v a -- ) store value v to address a
	(			ignore string until right parenthesis
	(again)		compile only code for the end of begin-again
				loop construct
	(begin)		compile only code for the begin of begin-again,
				begin-until, or begin-while-repeat loop construct
	(else)		compile only code for the else of if-else-then
				branch construct
	(for)		compile only code for the begin of for-next
				loop construct
	(if)		compile only code for the begin of if-else-then
				branch construct
	(next)		compile only code for the end of for-next
				loop construct
	(repeat)	compile only code for the end of begin-while-repeat 
				loop construct
	(then)		compile only code for the end of if-else-then
				branch construct
	(until)		compile only code for the end of begin-until
				loop construct
	(while)		compile only code for the while of 
				begin-while-repeat loop construct
	,			( n -- ) compile n into high level colon word-list
	.			( n -- ) print n and a space
	.(			print string until right parenthesis
	.id			( w -- ) print the id and name of given word w
	:			create high level definition word of given name
	;			end of high level definition
	?dup		( n -- n n | 0 ) duplicate n if n is not 0
	@			( a -- v ) fetch value v from address a
	=			( n1 n2 -- n1==n2 ) check if n1 equal to n2
	>r			( n -- ) push n onto return stack
	0=			( n -- n==0 ) check if n equal to 0
	1+			( n -- n+1 ) increment n by 1
	2dup		( n1 n2 -- n1 n2 n1 n2 ) duplicate n1 and n2
	cell/		( n -- n/4 ) divide n by 4
	compile		compile the word after
	constant	( n -- ) create constant of given name as value n
	context		( -- a ) the address of saving the last word in 
						 dictionary
	cr			print carriage return and line feed
	drop		( n -- ) drop n
	dup			( n -- n n ) duplicate n
	exit		exit from high level definition
	for			( n -- ) setup for-next loop to run the words
						 before next n+1 times
	here		( -- a ) the address of end of compiled space
	img			( -- a ) the address of a sample image
	immediate	set the last word to be immediate
	last		( -- a ) the address of saving the word just
						 defined but not in dictionary yet
	ms			( n -- ) delay n milli seconds
	next		end of for-next loop
	output		( pin -- ) setup given pin as an output device
	over		( n1 n2 -- n1 n2 n1 ) duplicate n1
	r@			( -- n ) duplicate the value n on return stack 
	r>			( -- n ) pop the value n on return stack
	swap		( n1 n2 -- n2 n1 ) swap two values on data stack
	toggle		( pin -- ) toggle HIGH/LOW level of given pin
	wb_drawLine		( x1 y1 x2 y2 color width -- ) 
	wb_drawImage	( x y w h adr -- )
	wb_drawString	( adr x y type size -- )
	wb_init			( -- )
	wb_setTextColor	( color -- )
	wbCYAN			( -- colorCYAN )
	wbRED			( -- colorRED )
	wbWHITE			( -- colorWHITE )
	z"			( -- adr ) the address of string before
						   double quote "
