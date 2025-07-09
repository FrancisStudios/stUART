/**
 *  ------ [ Property of Francis Studios ] ------
 * ==============================================
 * .. github:https://github.com/francisstudios ..
 * ____ ©2025 Francis Studios Softwares by L. ___
 */
#ifndef UTIL_H
#define UTIL_H

#pragma once

#include <Arduino.h>

namespace stUTIL
{
    void intToBinaryArray(int number, int binaryArray[8]);
    void setInputPins(int CLOCK_PIN, int DATA_PIN);
    int binaryArrayToInt(int binaryArray[8]);
    bool isMessageWithinLimit(int message, int limit);
}
#endif