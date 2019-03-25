# 為 Arduino 開扇門

在 esp32 的 WiFiBoy 開發板上, 我們逐步展示 一系列 簡單 blink 範例
 (都是使 WiFiBoy 板背 led 小燈持續不停 亮 1 秒 滅 1), 
如何為 Arduino  開扇夢幻後門。

所謂 後門, 就是在 Arduino 程式中, 啟動 所提供的 FVM 虛擬機 (virtual machine)。
在程式執行同時, 接受指令 以進行 檢視、監控、測試、 ... 等額外工作, 
或 直接改變 程式 執行狀態與效果。

在 blinkxx 資料夾 的 libraries 子目錄中 有 fvm 及 wifiboy_lib 兩個子目錄, 請先 複製到
Arduino user 的 libraries 工作子目錄, 例如在 windows 其路徑如下:
(請替換其中 <name> 為正確名字)

		C:\Users\<name>\Documents\Arduino\libraries


在 blinkxx 資料夾中還有 8 個 blink 範例 (依編號逐步增加其複雜度):
		
		blink00, blink01, blink02, blink03,
		blink10, blink11, blink12, blink13,


## blink00 範例

這範例 其實就是原 Arduino Basic Blink 範例, 我們多加了如下一行, 以定義 led 的 pin 腳號碼為 16。

		#define LED_BUILTIN 16 // for WIFIBOY 32


## blink01 範例

這範例在 blink00 中多加 3 行, 就啟動了 FVM 虛擬機。

1. 在 blink00 範例, setup() 前, 加如下兩行, 讓程式 載入 FVM 虛擬機:

		#include <fvm02.h>                      // ##### 1.1. load FVM class, the Forth virtual machine
		FVM F;                                  // ##### 1.2. define F as an instence of FVM


2. 在 blink00 範例, setup() 中, 多加如下 1 行, 讓程式 啟動 FVM 虛擬機:

		F.init( 115200 );                       // ##### 3.1. in setup(), initialize F


一旦 啟動了 FVM 虛擬機, 在 閃 led 同時, 我們可打開 Arduino IDE 的 Serial Monitor
從 input box 中, 可逐行輸入下列指令, 以關 led 燈、開屏幕背光、讓蜂鳴器發 C4 音、再多發 E4 與 A4 兩個音、讓蜂鳴器靜音、讓屏幕顯示圖片 1 秒後關閉。


		16 input
  		27 output 27 high
		25 17 buzzerSetup buzzerOn 261.6 tone
		329.6 tone 1000 ms  440.0 tone
		0 tone
		0 0 128 160 img wb_drawImage  1000 ms 27 output 27 low


此例第一行: 「16 input」 將 led 腳 (GPIO 16) 的 pin mode 設為 INPUT (原為 OUTPUT), 這樣 led 就不再亮了。


第二行: 「27 output」 將 屏幕背光 腳 (GPIO 27) 的 pin mode 設為 OUTPUT, 「27 high」 將該腳電位設為 HIGH, 這樣屏幕背光就亮了。


第三行: 「25 17 buzzerSetup」 指定 GPIO 25 與 GPIO 17 為 蜂鳴器 的 發聲 與 開關控制 腳,「buzzerOn」打開 蜂鳴器, 「261.6 tone」使 蜂鳴器 發出 261.6 HZ 頻率 鋼琴 中央 C (也就是 C4) 的音。


第四行: 「329.6 tone」使 蜂鳴器 發出 329.6 HZ 頻率 E4 的音,「1000 ms」使聲音維持 1 秒,「440.0」使 蜂鳴器 發出 440.0 HZ 頻率的 A4 音。


第五行: 「0 tone」使 蜂鳴器 靜音。


第六行: 「0 0 128 160 img wb_drawImage」 在屏幕 0,0 位置 畫出 寬 128 高 160 影像在 img 的圖片。「1000 ms」使圖片維持 1 秒。
「27 output 27 low」 將屏幕背光 pin 腳 (GPIO 27) 設為 OUTPUT, 並將該腳電位設為 LOW, 這樣屏幕背光關閉, 圖片就不見了。


## blink02 範例

這範例 主要是希望將 blink01 中的常數 以 led, delayHIGH, delayLOW 三個控制變數取代。
在 blink01 中多加 6 行, 就可下 虛擬機 指令, 特別是利用 虛擬機 的驚嘆號指令 來改變 控制變數的值。

1. 在 blink01 範例, #include <fvm.h> 前, 多加如下 3 行, 宣告 led, delayHIGH, delayLOW 為 3 個控制變數:

		int  led          = LED_BUILTIN;
		int  delayHIGH    = 1000;
		int  delayLOW     = 1000;


2. 以 led, delayHIGH, delayLOW 三個控制變數取代 blink01 中相關常數。


3. 在 blink01 範例, F.init() 之後, 多加如下 3 行, 讓虛擬機 分別知道 這三變數各自的記憶體位址:

		F.newVariable( "delayHIGH", &delayHIGH );
		F.newVariable( "delayLOW" , &delayLOW  );
		F.newVariable( "led"      , &led       );


一旦 這樣啟動了 FVM 虛擬機, 在 閃 led 同時, 我們打開 Arduino IDE 的 Serial Monitor
從 input box 中, 就可逐行輸入下列指令, 讓燈每秒短暫閃亮、讓燈快速閃亮、讓蜂鳴器滴答作響、關閉蜂鳴器。

		50 delayLOW  !
		50 delayHIGH !
		25 led ! 25 output 17 output 17 high
		25 input


此例第一行: 「50 delayLOW !」 其中的 驚嘆號 是指令 讀作 store, 它的作用就是 將 50 設為 delayLOW 這控制變數的 值 (原來的值 1000), 
將 led 腳的 LOW 電位 (led 亮) 改為維持 50 ms。 這樣就讓燈 每秒短暫閃亮了。


第二行: 「50 delayHIGH !」 將 50 設為 delayHIGH 這控制變數的 值 (原來的值 1000), 將 led 腳的 HIGH 電位 (led 滅) 也改為維持 50 ms。
這樣就讓燈 快速閃亮了。


第三行: 「25 led !」 將 25 設為 led 這控制變數的 值 (原來的值 16), 將 GPIO 25 (蜂鳴器 的 發聲腳) 當作 程式中 led 的電位輸出腳,
「25 output」設定 蜂鳴器 的 發聲腳 為 輸出,「17 output」設定 蜂鳴器 的 開關腳 為 輸出, 「17 high」將 蜂鳴器 打開。
這樣就讓蜂鳴器 滴答作響了。


第四行: 「25 input」設定 蜂鳴器 的 發聲腳 為 輸入。這樣就關閉了 蜂鳴器 。


## blink03 範例

這範例 要顯示如何增加 虛擬機 的 新指令, 以執行相關 控制功能。另一方面, 也是為確保記憶體安全,
藉此展示如何可 藉自訂 fuctions 以存取 控制變數, 而不讓 虛擬機 直接到記憶體存取 控制變數的值。

1. 在 blink02 範例, setup() 前, 定義  Arduino functions, 以設定 led 亮/滅 時間, 以及 led 。

		void setDelayHIGH() { periodHIGH=F.dPop(); }       // ##### 2.1. define the function setDelayHIGH
		void setDelayLOW()  { periodLOW =F.dPop(); }       // ##### 2.2. define the function setDelayLOW
		void setLed()       { led       =F.dPop(); }       // ##### 2.3. define the function setLed


2. setup() 中, 定義 3 個 虛擬機指令, 以分別執行 對應的 Arduino function。

		F.newPrimitive( "setDelayHIGH", setDelayHIGH );    // ##### 4.1. add new primitive word setDelayHIGH in F
		F.newPrimitive( "setDelayLOW",  setDelayLOW  );    // ##### 4.2. add new primitive word setDelayLOW  in F
		F.newPrimitive( "setLed"     ,  setLed       );    // ##### 4.3. add new primitive word setLed       in F
  

一旦 這樣啟動了 FVM 虛擬機, 在 閃 led 同時, 我們打開 Arduino IDE 的 Serial Monitor
從 input box 中, 就可逐行輸入下列指令, 讓燈每秒短暫閃亮、讓燈快速閃亮、讓蜂鳴器滴答作響、關閉蜂鳴器。

		50 setDelayLOW
		50 setDelayHIGH
		25 setLed 25 output 17 output 17 high
		25 input


此例第一行: 「50 setDelayLOW」 將 50 設為 delayLOW 這控制變數的 值 (原來的值 1000), 
將 led 腳的 LOW 電位 (led 亮) 改為維持 50 ms。 這樣就讓燈 每秒短暫閃亮了。


第二行: 「50 setDelayHIGH」 將 50 設為 delayHIGH 這控制變數的 值 (原來的值 1000), 將 led 腳的 HIGH 電位 (led 滅) 也改為維持 50 ms。
這樣就讓燈 快速閃亮了。


第三行: 「25 setLed」 將 25 設為 led 這控制變數的 值 (原來的值 16), 將 GPIO 25 (蜂鳴器 的 發聲腳) 當作 程式中 led 的電位輸出腳,
「25 output」設定 蜂鳴器 的 發聲腳 為 輸出,「17 output」設定 蜂鳴器 的 開關腳 為 輸出, 「17 high」將 蜂鳴器 打開。
這樣就讓蜂鳴器 滴答作響了。


第四行: 「25 input」設定 蜂鳴器 的 發聲腳 為 輸入。這樣就關閉了 蜂鳴器 。


## blink10 範例

這範例 改寫 blink00, 在 loop() 子程式中, 不用 delay() 來維持 亮/滅 時間, 改以 millis() 檢視時間,
直到過了 指定時間 才改變 亮/滅 並 設定下一個檢視時間。 這樣的設計 可讓我們有機會 善用 1 秒 的等待時間 去做些別的事。
程式中增加 timeToChange 與 levelToChange 這兩個變數, 用以儲存 何時該改變 led 狀態, 以及要改變為怎樣的輸出電位。


## blink11 範例

這範例在 blink10 中多加 3 行, 就啟動了 FVM 虛擬機。

1. 在 blink10 範例, setup() 前, 加如下兩行, 讓程式 載入 FVM 虛擬機:

		#include <fvm02.h>                      // ##### 1.1. load FVM class, the Forth virtual machine
		FVM F;                                  // ##### 1.2. define F as an instence of FVM


2. 在 blink10 範例, setup() 中, 多加如下 1 行, 讓程式 啟動 FVM 虛擬機:

		F.init( 115200 );                       // ##### 3.1. in setup(), initialize F


一旦 啟動了 FVM 虛擬機, 在 閃 led 同時, 我們可打開 Arduino IDE 的 Serial Monitor
從 input box 中, 可逐行輸入下列指令, 以關 led 燈、開屏幕背光、讓蜂鳴器發 C4 音、再多發 E4 與 A4 兩個音、讓蜂鳴器靜音、讓屏幕顯示圖片 1 秒後關閉。

		16 input
  		27 output 27 high
		25 17 buzzerSetup buzzerOn 261.6 tone
		329.6 tone 1000 ms  440.0 tone
		0 tone
		0 0 128 160 img wb_drawImage  1000 ms 27 output 27 low


此例第一行: 「16 input」 將 led 腳 (GPIO 16) 的 pin mode 設為 INPUT (原為 OUTPUT), 這樣 led 就不再亮了。


第二行: 「27 output」 將 屏幕背光 腳 (GPIO 27) 的 pin mode 設為 OUTPUT, 「27 high」 將該腳電位設為 HIGH, 這樣屏幕背光就亮了。


第三行: 「25 17 buzzerSetup」 指定 GPIO 25 與 GPIO 17 為 蜂鳴器 的 發聲 與 開關控制 腳,「buzzerOn」打開 蜂鳴器, 「261.6 tone」使 蜂鳴器 發出 261.6 HZ 頻率 鋼琴 中央 C (也就是 C4) 的音。


第四行: 「329.6 tone」使 蜂鳴器 發出 329.6 HZ 頻率 E4 的音,「1000 ms」使聲音維持 1 秒,「440.0」使 蜂鳴器 發出 440.0 HZ 頻率的 A4 音。


第五行: 「0 tone」使 蜂鳴器 靜音。


第六行: 「0 0 128 160 img wb_drawImage」 在屏幕 0,0 位置 畫出 寬 128 高 160 影像在 img 的圖片。「1000 ms」使圖片維持 1 秒。
「27 output 27 low」 將屏幕背光 pin 腳 (GPIO 27) 設為 OUTPUT, 並將該腳電位設為 LOW, 這樣屏幕背光關閉, 圖片就不見了。


## blink12 範例

這範例 主要是希望將 blink11 中的常數 以 led, delayHIGH, delayLOW 三個控制變數取代。
在 blink01 中多加 6 行, 就可下 虛擬機 指令, 特別是利用 虛擬機 的驚嘆號指令 來改變 控制變數的值。

1. 在 blink11 範例, #include <fvm.h> 前, 多加如下 3 行, 宣告 led, delayHIGH, delayLOW 為 3 個控制變數:

		int  led          = LED_BUILTIN;
		int  delayHIGH    = 1000;
		int  delayLOW     = 1000;


2. 以 led, delayHIGH, delayLOW 三個控制變數取代 blink01 中相關常數。


3. 在 blink11 範例, F.init() 之後, 多加如下 3 行, 讓虛擬機 分別知道 這三變數各自的記憶體位址:

		F.newVariable( "\x0d" "delayHIGH", &delayHIGH );
		F.newVariable( "\x0c" "delayLOW" , &delayLOW  );
		F.newVariable( "\x05" "led"      , &led       );


一旦 這樣啟動了 FVM 虛擬機, 在 閃 led 同時, 我們打開 Arduino IDE 的 Serial Monitor
從 input box 中, 就可逐行輸入下列指令, 讓燈每秒短暫閃亮、讓燈快速閃亮、讓蜂鳴器滴答作響、關閉蜂鳴器。

		50 delayLOW  !
		50 delayHIGH !
		25 led ! 25 output 17 output 17 high
		25 input


此例第一行: 「50 delayLOW !」 其中的 驚嘆號 是指令 讀作 store, 它的作用就是 將 50 設為 delayLOW 這控制變數的 值 (原來的值 1000), 
將 led 腳的 LOW 電位 (led 亮) 改為維持 50 ms。 這樣就讓燈 每秒短暫閃亮了。


第二行: 「50 delayHIGH !」 將 50 設為 delayHIGH 這控制變數的 值 (原來的值 1000), 將 led 腳的 HIGH 電位 (led 滅) 也改為維持 50 ms。
這樣就讓燈 快速閃亮了。


第三行: 「25 led !」 將 25 設為 led 這控制變數的 值 (原來的值 16), 將 GPIO 25 (蜂鳴器 的 發聲腳) 當作 程式中 led 的電位輸出腳,
「25 output」設定 蜂鳴器 的 發聲腳 為 輸出,「17 output」設定 蜂鳴器 的 開關腳 為 輸出, 「17 high」將 蜂鳴器 打開。
這樣就讓蜂鳴器 滴答作響了。


第四行: 「25 input」設定 蜂鳴器 的 發聲腳 為 輸入。這樣就關閉了 蜂鳴器 。


## blink13 範例

這範例 要顯示如何增加 虛擬機 的 新指令, 以執行相關 控制功能。另一方面, 也是為確保記憶體安全,
藉此展示如何可 藉自訂 fuctions 以存取 控制變數, 而不讓 虛擬機 直接到記憶體存取 控制變數的值。

1. 在 blink12 範例, setup() 前, 定義  Arduino functions, 以設定 led 亮/滅 時間, 以及 led 。

		void setDelayHIGH() { periodHIGH=F.dPop(); }       // ##### 2.1. define the function setDelayHIGH
		void setDelayLOW()  { periodLOW =F.dPop(); }       // ##### 2.2. define the function setDelayLOW
		void setLed()       { led       =F.dPop(); }       // ##### 2.3. define the function setLed


2. setup() 中, 定義 3 個 虛擬機指令, 以分別執行 對應的 Arduino function。

		F.newPrimitive( "\x0d" "setDelayHIGH", setDelayHIGH ); // ##### 4.1. add new primitive word setDelayHIGH in F
		F.newPrimitive( "\x0c" "setDelayLOW",  setDelayLOW  ); // ##### 4.2. add new primitive word setDelayLOW  in F
		F.newPrimitive( "\x06" "setLed"     ,  setLed       ); // ##### 4.3. add new primitive word setLed       in F
  

一旦 這樣啟動了 FVM 虛擬機, 在 閃 led 同時, 我們打開 Arduino IDE 的 Serial Monitor
從 input box 中, 就可逐行輸入下列指令, 讓燈每秒短暫閃亮、讓燈快速閃亮、讓蜂鳴器滴答作響、關閉蜂鳴器。

		50 setDelayLOW
		50 setDelayHIGH
		25 setLed 25 output 17 output 17 high
		25 input


此例第一行: 「50 setDelayLOW」 將 50 設為 delayLOW 這控制變數的 值 (原來的值 1000), 
將 led 腳的 LOW 電位 (led 亮) 改為維持 50 ms。 這樣就讓燈 每秒短暫閃亮了。


第二行: 「50 setDelayHIGH」 將 50 設為 delayHIGH 這控制變數的 值 (原來的值 1000), 將 led 腳的 HIGH 電位 (led 滅) 也改為維持 50 ms。
這樣就讓燈 快速閃亮了。


第三行: 「25 setLed」 將 25 設為 led 這控制變數的 值 (原來的值 16), 將 GPIO 25 (蜂鳴器 的 發聲腳) 當作 程式中 led 的電位輸出腳,
「25 output」設定 蜂鳴器 的 發聲腳 為 輸出,「17 output」設定 蜂鳴器 的 開關腳 為 輸出, 「17 high」將 蜂鳴器 打開。
這樣就讓蜂鳴器 滴答作響了。


第四行: 「25 input」設定 蜂鳴器 的 發聲腳 為 輸入。這樣就關閉了 蜂鳴器 。


## 相關準備

### 1. 為 Arduino IDE 安裝 esp32 選項

請參閱 https://wifiboy.club/category/9/wifiboy32-esp32 檢視「如何安裝 Arduino IDE for WiFiBoy32」


### 2. 從 github 取得 blinkxx 相關資料

	git clone https://github.com/samsuanchen/blinkxx

### 3. 將 fvm 及 wifiboy_lib 加入 Arduino libraries

	將 fvm 與 wifiboy_lib 資料夾 加入 Arduino IDE 的 libraries

## FVM 虛擬機 功能 簡要說明

	FVM F				clame F as an instance of FVM.
	F.init(baud)			initialize F with given baud rate.
	F.init(baud,cpu)		initialize F with given baud rate to run at given cpu.
	F.newPrimitive(name,func)	create new primitive type word of given name to run given function.
	F.newConstant(name,number)	create new constant type word of given name to return given number.
	F.newVariable(name,address)	create new variable type word of given name to return given address.


## 虛擬機 test.txt 範例 引用的指令 簡要說明

	'		( <name> -- w )	find the word of given name
	-		( n1 n2 -- n1-n2 ) subtract n1 by n2
	!		( v a -- ) store value v to address a
	(		ignore string until right parenthesis
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
	,		( n -- ) compile n into high level colon word-list
	.		( n -- ) print n and a space
	.(		print string until right parenthesis
	.id		( w -- ) print the id and name of given word w
	:		create high level definition word of given name
	;		end of high level definition
	?dup		( n -- n n | 0 ) duplicate n if n is not 0
	@		( a -- v ) fetch value v from address a
	=		( n1 n2 -- n1==n2 ) check if n1 equal to n2
	>r		( n -- ) push n onto return stack
	0=		( n -- n==0 ) check if n equal to 0
	1+		( n -- n+1 ) increment n by 1
	2dup		( n1 n2 -- n1 n2 n1 n2 ) duplicate n1 and n2
	cell/		( n -- n/4 ) divide n by 4
	compile		compile the word after
	constant	( n -- ) create constant of given name as value n
	context		( -- a ) the address of saving the last word in 
			dictionary
	cr		print carriage return and line feed
	drop		( n -- ) drop n
	dup		( n -- n n ) duplicate n
	exit		exit from high level definition
	for		( n -- ) setup for-next loop to run the words
				before next n+1 times
	here		( -- a ) the address of end of compiled space
	img		( -- a ) the address of a sample image
	immediate	set the last word to be immediate
	last		( -- a ) the address of saving the word just
				defined but not in dictionary yet
	ms		( n -- ) delay n milli seconds
	next		end of for-next loop
	output		( pin -- ) setup given pin as an output device
	over		( n1 n2 -- n1 n2 n1 ) duplicate n1
	r@		( -- n ) duplicate the value n on return stack 
	r>		( -- n ) pop the value n on return stack
	swap		( n1 n2 -- n2 n1 ) swap two values on data stack
	toggle		( pin -- ) toggle HIGH/LOW level of given pin
	wb_drawLine	( x1 y1 x2 y2 color width -- ) 
	wb_drawImage	( x y w h adr -- )
	wb_drawString	( adr x y type size -- )
	wb_init		( -- )
	wb_setTextColor	( color -- )
	wbCYAN		( -- colorCYAN )
	wbRED		( -- colorRED )
	wbWHITE		( -- colorWHITE )
	z"		( -- adr ) the address of string before double quote "
