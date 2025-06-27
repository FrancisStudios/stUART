#include "stuart.h"
#include "util.cpp"

int stUART::TIME_FRAME = 0;
int stUART::CLOCK_PIN = 0;
int stUART::DATA_PIN = 0;

void stUART::begin(int timeFrame, int CLOCK, int DATA)
{
    TIME_FRAME = timeFrame;
    CLOCK_PIN = CLOCK;
    DATA_PIN = DATA;
}

void stUART::transmit(int message)
{
    int binaryArray[8];

    /** Input data validation and waiting for time to speak */
    if (CLOCK_PIN > 0 && DATA_PIN > 0 && TIME_FRAME > 0)
        pinMode(CLOCK_PIN, INPUT);
    else
        return;

    while (digitalRead(CLOCK_PIN) == HIGH)
    {
        delay(TIME_FRAME);
    }

    /** Starting transmission */
    pinMode(CLOCK_PIN, OUTPUT);
    digitalWrite(CLOCK_PIN, HIGH);
    delay(5 * TIME_FRAME);
    digitalWrite(CLOCK_PIN, LOW);
    delay(TIME_FRAME);

    /** Transmission encoder */
    // stUTIL::intToBinaryArray(message, binaryArray); TODO: fix this to fill up binary array

    for (int i = 0; i < 8; ++i)
    {
        digitalWrite(CLOCK_PIN, HIGH);
        digitalWrite(DATA_PIN, binaryArray[i]);
        delay(TIME_FRAME);
        digitalWrite(CLOCK_PIN, LOW);
        delay(TIME_FRAME);
    }
}

int stUART::receive()
{
}