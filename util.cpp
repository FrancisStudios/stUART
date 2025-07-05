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

    void setInputPins(int CLOCK_PIN, int DATA_PIN)
    {
        pinMode(CLOCK_PIN, INPUT);
        pinMode(DATA_PIN, INPUT);
    }
}