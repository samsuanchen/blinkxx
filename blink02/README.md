# blink02
This project is derived from my blink01 (https://github.com/samsuanchen/blink01). A virtual machine, my fvm02 (https://github.com/samsuanchen/fvm02), is includeded and activated so that while blinking we could do some thing else, for example to draw image, lines, and characters on wifiboy screen.

01. To include virtual machine fvm02, 2 lines are added into blink01:

        #include <fvm02.h>                                  // ##### 1.1. load FVM the Forth virtual machine
        FVM F;                                              // ##### 1.2. define F as an instence of FVM


02. To initialize the virtual machine and its word set, in setup(), 2 lines are added into blink01:

        extern Word* word_set;                            // ##### 3.1. load external word set (defined in fvm02_word_set.cpp)
        F.init( 115200, word_set );                       // ##### 3.2. in setup(), initialize F and the word set


03. To update the virtual machine state, in loop(), 1 line is added into blink01:

        F.update();                                       // ##### 5. in loop(), update F state


04. Once this code is running, in the same time while blinking, the virtual machine fvm02 is includeded and activated.

05. On Arduino IDE, select Board.

![width:50%; height:50%;](https://github.com/samsuanchen/blink02/blob/master/jpg/selectBoard.jpg)

06. Select Port.

![width:50%; height:50%;](https://github.com/samsuanchen/blink02/blob/master/jpg/selectPort.jpg)

07. Open interactive working console. 

![width:50%; height:50%;](https://github.com/samsuanchen/blink02/blob/master/jpg/openConsole.jpg)

08. A forth script in test.txt as follows could be pasted into Arduino IDE input box:

        wb_init ( initialize wifiboy lib )
        0 0 128 160 img wb_drawImage ( draw image tsuzu )
        2000 ms ( wait 2000 ms )
        : drawLines ( define a code to draw lines )
          42 for 1 1 r@ 3 * 1+ 159 wbRED 1 wb_drawLine next 
          51 for 1 1 127 r@ 3 * 1+ wbRED 1 wb_drawLine next
        ; drawLines ( draw lines )
        wbCYAN wbCYAN wb_setTextColor ( set text color )
        z" WiFiBoy" 28 10 1 3 wb_drawString drop ( draw "WiFiBoy" )
        z" blink02" 42 138 2 2 wb_drawString drop ( draw "blink0x" )
        wbWHITE wbWHITE wb_setTextColor ( set text color )
        z" FVM02" 22 120 2 2 wb_drawString drop ( draw "Forth" )

![width:50%; height:50%;](https://github.com/samsuanchen/blink02/blob/master/jpg/pasteScript.jpg)

07. After clicking the button Send, an image, some lines, and some characters will be shown on wifiboy screen.

![width:50%; height:50%;](https://github.com/samsuanchen/blink02/blob/master/jpg/drawScreen.jpg)
