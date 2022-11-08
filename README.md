# PIC16F1939-stopwatch

This project is a simple stopwatch system using a microcontroller board based on PIC16F1939 microcontroller, 4 7-segment displays, and 3 buttons, 
with a resolution of one second, which means the maximum time that can be measured is 99 minutes and 59 seconds, 
the three buttons are for starting time, pausing/stoping time, and showing time in binary form on LEDs on the microcontroller board.

## Hardware

- Microcontroller board (based on PIC16F1939, made by our faculty) scheme/connections are shown 
[here](https://c2.etf.unsa.ba/pluginfile.php/20672/mod_resource/content/0/Razvojni_sistem_PIC16F877_V1.pdf).
- 7-segment display that is used is with a common anode and has a segment/led for displaying the dot.
- Three ordinary two-terminated buttons were used as pull-down pushbuttons.
- Realistic connecting scheme and the microcontroller are shown below: (for electrical scheme see
[documentation](https://docs.google.com/viewer?url=https://github.com/Yaly0/PIC16F1939-stopwatch/files/7919305/Izvjestaj.pdf.pdf) p. 9 and 10).

|<img width="520" alt="Screenshot 2019-02-04 at 8 29 10 PM" src="https://user-images.githubusercontent.com/95139567/149965861-ad42a0d8-537b-415f-bcea-fe12810a99d1.png">|<img width="350" alt="Screenshot 2019-02-04 at 8 29 10 PM" src="https://user-images.githubusercontent.com/95139567/150783105-54baf570-ff26-4f06-a6e3-71845b20a0fd.jpeg">|
|-|-|

## Software

The program was coded in MPLAB X IDE, an IDE for the development of embedded applications on PIC microcontrollers, it uses the languages C and assembler, 
this project was coded in low-level C.

The MPLAB X IDE has a simulator where all output pins' states can be seen, and all input pins can be manually changed, 
the simulation was used for all program functionalities, and because of it, no modifications were needed after connecting the scheme for the first time.

---
For more information see 
[documentation](https://docs.google.com/viewer?url=https://github.com/Yaly0/PIC16F1939-stopwatch/files/7919305/Izvjestaj.pdf.pdf) (written in Bosnian language).
