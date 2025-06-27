#include "stuart.h"

int stUART::TIME_FRAME;
int stUART::CLOCK_PIN;
int stUART::DATA_PIN;

void stUART::begin(int timeFrame, int CLOCK, int DATA)
{
    TIME_FRAME = timeFrame;
    CLOCK_PIN = CLOCK;
    DATA_PIN = DATA;
}

void stUART::transmit(int message)
{
}

int stUART::receive()
{
}