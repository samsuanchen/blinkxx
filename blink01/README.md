# blink01
Not using delay(), an alternative blink is given to run in the same feature of the Arduino basic example Blink  (http://www.arduino.cc/en/Tutorial/Blink).


Using delay(), the CPU cannot do anything else in the same time period.

In this project, our alternative blink is given so that the CPU is available to do something else in the same time period. 


The function millis() is used to check CPU running time in ms (milli seconds), since CPU reset or powered on.


Four controle variables are used:

    1. The variable changLevel is used to remember LED pin level (HIGH/LOW) to change.
    2. The variable timeChangeLevel is used to remember the time to change LED pin level (HIGH/LOW).
    3. The variable periodHIGH is used to remember the time delay period for LED pin level HIGH.
    4. The variable periodLOW is used to remember the time delay period for LED pin level LOW.


To keep the same feature of the Arduino basic example Blink, periodHIGH and periodLOW both are set to be 1000.


In setup(), once LED pin is set up as a digital OUTPUT device, LED pin level is autometically set to LOW (turn on LED).

So, 

    1. periodLOW is set to timeChangeLevel and
    2. HIGH is set to changLevel, initially. 


In loop(), the code waits until timeChangeLevel to get into if statement to

    1. LED pin level is set to changLevel.
    2. timeChangeLevel is updated.
    3. changLevel is toggled.
