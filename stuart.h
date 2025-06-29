/**
 *  ------ [ Property of Francis Studios ] ------
 * ==============================================
 * .. github:https://github.com/francisstudios ..
 * ____ ©2025 Francis Studios Softwares by L. ___
 */

#ifndef STUART_H
#define STUART_H

#pragma once

#include <Arduino.h> //(un)comment if you are (not) using arduino
/** This library is currently written for arduino ecosystem primarily
so delay and other arduino implementations must be ported manually to
each environment -- will be included in this library in the future (pbbly)
-- it might be a good way to contribute for anyone, just drop a PR xD :)
*/

class stUART
{
public:
    static int TIME_FRAME, CLOCK_PIN, DATA_PIN;

    /* Function prototypes for main class*/
    static void begin(int timeFrame, int CLOCK, int DATA);
    static void transmit(int message);
    static int receive(int DATA_FRAME, bool DATA_FRAME_DONE_SIGNAL);

private:
    static void clockOnTimer(bool CURRENT_CLOCK_STATUS, bool PREVIOUS_CLOCK_STATUS);
    static void dataBitsCounter(bool CURRENT_CLOCK_STATUS, bool PREVIOUS_CLOCK_STATUS);
};
#endif