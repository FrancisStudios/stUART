# 🐭 stUART

`by Francis Studios`

## ❓ What is stUART? 

Stuart is an i2c communication protocol, that uses 2 wires to interface between two circuits (**CLK** and **DATA**) and send 8 bit frames (similarly to UART) but this is a simplistic _"very stupid"_ method for simple embedded applications. 

This repository **contains the C/C++ library** implementation for microcontrollers or programmable chip(set)s.

## ⌨️ Usage

## 🔌 API reference

## 📁 Files

## 💭 Theoretical knowledge

**In this section I'm attempting to explain how this communication protocol works**

Preconception:
`I wanted a simple communication protocol that can simply transmit a few numbers between microcontrollers, and I'm using Attiny45 and that kinda stuff in this project, so we would like to keep the number of pins used to the minimum`

- ⏰ CLOCK : the clock line is by default **low** unless someone wants to speak. If a member tries to speak up, it pulls the CLK line **high** for `timeFrame x 5` ms then a clock pulse for every single **data bit** which can be high or low

- 💾 DATA : data is transmitted on the data line during every clock pulse which can be **digital high** or **digital low**. Data is organized into **frames**. A frame consists of the 5 timeFrame long **call signal** and **8 bits** of data which is then converted into an integer.

- 🪟 TIME_FRAME : time frame is a delay time in milliseconds of how long a pulse should last. Choose this wisely, knowing the limitations of your target system. 