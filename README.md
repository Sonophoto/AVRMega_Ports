
# AVRMega_Ports

Library for fast access to Arduino ATmega2560 digital pins 22-53

I'm still working on this but you will find the readMega and writeMega functions are fully tested.

You can figure out what I'm doing by looking at the code. 

hit me up if you find this, want to use it, and aren't sure what to do next ;-)

Update 24-Mar-2017
------------------

Finally got the fundamental structure of the library setup and working.

NOTE: Currently I am still adding and testing functionality but you can use this right now.

NOTE: This library is built ON a POSIX (unix) system but it will work in ANY Arduino IDE on ANY OS

NOTE: This library is built FOR an "Arduino Mega" AKA AVR ATMega2560. It won't work on any other type of ARDUINO "as-is" but you could use this as an example to build a similar library using the ports available on the hardware you do have. I have zero motivation to do this myself but I am giving you a BSD-2c license to use this code any anyway you see fit! Please Fork! ;-)

Update 23-Mar-2017
------------------

This library is currently under development but you can use it right now!

Massive reorganization results in usable code:

     USAGE:
 
          1. Clone entire project directory into you Arduino libraries directory

          2. #include mega2560_ports.h

          3. Use the literals and functions to do your thing


Reorganized all of the code into a more conventional format after browsing thru
   some of the standard libraries that come with Arduino.
   
Added a keywords.txt file for syntax higlighting the libraries members

Added a new directory for a program "Logica" that will demonstrate the library.
   Hopefully, this might turn out to be a useful arduino application as well.

Added a new directory "tests" an Arduino project that runs the test suite.

Added a libraries.properties file for the arduino archives.

Update 22-Mar-2017
------------------

Moved the defines and functions into seperate include files, both are required.

    USAGE: Drop both .h files into the root of your project and #include them in your code.
    
This is set up as a single file include system so the functions are defined in the .h file.
 

Update 19-Mar-2017
------------------

I'm still working on this but you will find the readMega and writeMega functions are fully tested.

You can figure out what I'm doing by looking at the code. 

hit me up if you find this, want to use it, and aren't sure what to do next ;-)

I will be turning this into a complete Arduino libary over the next couple of weeks.

This is a 100% unpaid project so it gets time when I'm bored.
