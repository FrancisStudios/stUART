# 🐭 stUART

`by Francis Studios`

Current version is `v1.0` 🟢

Release date : `2025.07` 📅 

## ❓ What is stUART? 

Stuart is an i2c communication protocol, that uses 2 wires to interface between two circuits (**CLK** and **DATA**) and send 8 bit frames (similarly to UART) but this is a simplistic _"very stupid"_ method for simple embedded applications. 

This repository **contains the C/C++ library** implementation for microcontrollers or programmable chip(set)s.

## ⌨️ Usage

It starts with Arduino. Currently only arduino environment is supported by this library. In the future I plan to extend this for other MCUs and maybe FPGAs. 

1. Clone this repo to your system (see clone option up above)
2. Copy the repository to ``Documents/Arduino/libraries/`` folder (or wherever you installed your Arduino IDE)
3. Include it in your project ``#include <stuart.h>``
4. Connect two uController devices together (currenly Arduino is supported) [Select two GPIO pins for CLOCK and DATA]
5. Check the example files below
6. Upload transmit and receive onto different devices
7. Have fun :) 

## 🔌 API reference

### 1) 🏁 .begin()
```cpp
void stUART::begin(int timeFrame, int CLOCK, int DATA);
```

This function must be used in the ``setup()`` section of your code. This should only be called once and accepts the timeFrame (milliseconds) and the CLOCK pin number and DATA pin number. 

### 2) 📡 .transmit()
```cpp
bool stUART::transmit(int message);
```

With this method you can transmit any number that can fit in an 8 bit frame (from **0x00 to 0xFF** a.k.a. 0-256 in decimal)- for larger numbers my suggestion is to break it up to digits and transmit in a digit based, or two digit based system - whatever fits your needs. 

This function returns a **boolean** depending on if the transmission procedure is ready to start. Here is an example:

```CPP
if (stUART::transmit())
      stUART::transmit(message[i]);
```
If transmit returns with true, you can start transmitting your message

Here is the full transmit example:
_Let's imagine, that you want to transmit the large number of 1234 (decimal) over this protocol. First you have to splice it up to singe (or double) digits and create a list or array of it and transmit those single/double digits like shown_

```CPP
#include <stuart.h>

void setup() {
  stUART::begin(100, 6, 5);
}

void loop() {
  int message[4] = { 1, 2, 3, 4 };

  for (int i = 0; i < 4; i++) {
    if (stUART::transmit())
      stUART::transmit(message[i]);
  }
}

```

Example file: [📁 arduino_send.ino](/examples/arduino_send.ino)

### 2) 📶 .receive()
```cpp
int stUART::receive();
```

This method returns an ``integer`` number transmitted via the 8bit frame.

The largest number you can fit in the 8bit frame is ``0b11111111`` which equals to 255 decimal (this shouldn't surprise you, basic computing knowledge) so **this function returns 256** in any case where the frame is not ready yet. So you can check your transmission package state like so:

```CPP
void loop() {
  int result = stUART::receive();
  if (result < 0xFF) Serial.println(result); //check if frame is ready
}
```

here is a recieve example:
```CPP
#include <stuart.h>

void setup() {
  Serial.begin(9600);
  stUART::begin(100, 6, 5);
}

void loop() {
  int result = stUART::receive();
  if (result < 0xFF) Serial.println(result);
}

```
and the example file below:

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