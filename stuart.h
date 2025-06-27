#ifndef STUART_H
#define STUART_H

#pragma once

#include <Arduino.h> //(un)comment if you are (not) using arduino 
/** This library is currently written for arduino ecosystem primarily
so delay and other arduino implementations must be ported manually to
each environment -- will be included in this library in the future (pbbly)
-- it might be a good way to contribute for anyone, just drop a PR xD :)
*/

class stUART {
    public:
        static void begin(int timeFrame, int CLOCK, int DATA);
};

#endif