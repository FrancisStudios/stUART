# 🐭 stUART

`by Francis Studios`

## ❓ What is stUART? 

Stuart is an i2c communication protocol, that uses 2 wires to interface between two circuits (**CLK** and **DATA**) and send 8 bit frames (similarly to UART) but this is a simplistic _"very stupid"_ method for simple embedded applications. 

This repository **contains the C/C++ library** implementation for microcontrollers or programmable chip(set)s.

## ⌨️ Usage

It starts with Arduino. Currently only arduino environment is supported by this library. In the future I plan to extend this for other MCUs and maybe FPGAs. 

1. Clone this repo to your system
2. Copy the repository to ``Documents/Arduino/libraries`` folder (or wherever you installed your Arduino IDE)
3. Include it in your project ``#include <stuart.h>``

## 🔌 API reference

### 1) 🏁 .begin()
```cpp
stUART::begin(int timeFrame, int CLOCK, int DATA);
```

This function must be used in the ``setup()`` section of your code. This should only be called once and accepts the timeFrame (milliseconds) and the CLOCK pin number and DATA pin number. 

### 2) 📡 .transmit()
```cpp
stUART::transmit(int message);
```

With this method you can transmit any number that can fit in an 8 bit frame - for larger numbers my suggestion is to break it up to digits and transmit in a digit based, or two-three-four digit based system - whatever fits your needs. 

Example file: [📁 arduino_send.ino](/examples/arduino_send.ino)

### 2) 📶 .receive()
```cpp
stUART::receive();
```

This method returns a number that was transmitted in the 8bit frame. ``STILL WORK IN PROGRESS`` 

Example file: [📁 arduino_receive.ino](/examples/arduino_receive.ino)

Equivalent arduino project: [📁 reader.cpp](/examples/reader.cpp.old)

## 📁 Files

## 💭 Theoretical knowledge

**In this section I'm attempting to explain how this communication protocol works**

Preconception:
`I wanted a simple communication protocol that can simply transmit a few numbers between microcontrollers, and I'm using Attiny45 and that kinda stuff in this project, so we would like to keep the number of pins required to the minimum`

- ⏰ CLOCK : the clock line is by default **low** unless someone wants to speak. If a member tries to speak up, it pulls the CLK line **high** for `timeFrame x 5` ms then a clock pulse for every single **data bit** which can be high or low 
![clock signal](/docs/clock_signal.png)

- 💾 DATA : data is transmitted on the data line during every clock pulse which can be **digital high** or **digital low**. Data is organized into **frames**. A frame consists of the 5 timeFrame long **call signal** and **8 bits** of data which is then converted into an integer.

- 🪟 TIME_FRAME : time frame is a delay time in milliseconds of how long a pulse should last. Choose this wisely, knowing the limitations of your target system. 