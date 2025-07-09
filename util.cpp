/**
 *  ------ [ Property of Francis Studios ] ------
 * ==============================================
 * .. github:https://github.com/francisstudios ..
 * ____ ©2025 Francis Studios Softwares by L. ___
 */

#include "util.h"
namespace stUTIL
{
    /* Converts int to binary array for further processing */
    void intToBinaryArray(int number, int binaryArray[8])
    {
        for (int i = 7; i >= 0; --i)
        {
            int bit = (number >> i) & 1;
            binaryArray[7 - i] = bit;
        }
    }

    int binaryArrayToInt(int binaryArray[8])
    {
        int number = 0;
        for (int i = 0; i < 8; ++i)
        {
            number = (number << 1) | (binaryArray[i] & 1);
        }
        return number;
    }

    void setInputPins(int CLOCK_PIN, int DATA_PIN)
    {
        pinMode(CLOCK_PIN, INPUT);
        pinMode(DATA_PIN, INPUT);
    }

    bool isMessageWithinLimit(int message, int limit)
    {
        return message < limit;
    }
}