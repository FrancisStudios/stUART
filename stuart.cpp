/**
 *  ------ [ Property of Francis Studios ] ------
 * ==============================================
 * .. github:https://github.com/francisstudios ..
 * ____ ©2025 Francis Studios Softwares by L. ___
 */

#include "stuart.h"
#include "util.h"

int stUART::TIME_FRAME = 0;
int stUART::CLOCK_PIN = 0;
int stUART::DATA_PIN = 0;

bool TEST_ENVIRONMENT = true;

struct CLOCK_STATE_S
{
    bool CURRENT;
    bool PREVIOUS;
};

CLOCK_STATE_S CLOCK_STATE;

struct TIMER_S
{
    long START; // TIMER USED FOR TIMING CLOCK
    bool IS_STARTED;
};

TIMER_S TIMER;

struct CALL_SIGN_S
{
    bool IS_CALLED;     // LONG HIGH PERIOD REACHED TRESHOLD
    bool IS_REGISTERED; // IS PULLED LOW AFTER TRESHOLD -> DATA STREAM CAN BEGIN
};

CALL_SIGN_S CALL_SIGN;

struct DATA_S
{
    int COUNTER;
    int STORE[8];
    bool DONE;
};

DATA_S DATA_FRAME;

/* EXPORTED STUART FNS */
void stUART::begin(int timeFrame, int CLOCK, int DATA)
{
    TIME_FRAME = timeFrame;
    CLOCK_PIN = CLOCK;
    DATA_PIN = DATA;
}

void stUART::transmit(int message)
{
    int encodeBinaryArray[8];

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
    pinMode(DATA_PIN, OUTPUT);
    digitalWrite(CLOCK_PIN, HIGH);
    delay(5 * TIME_FRAME);
    digitalWrite(CLOCK_PIN, LOW);
    delay(TIME_FRAME);

    /** Transmission encoder */
    stUTIL::intToBinaryArray(message, encodeBinaryArray);

    for (int i = 0; i < 8; ++i)
    {
        digitalWrite(CLOCK_PIN, HIGH);
        digitalWrite(DATA_PIN, encodeBinaryArray[i]);
        delay(TIME_FRAME);
        digitalWrite(CLOCK_PIN, LOW);
        digitalWrite(DATA_PIN, LOW);
        delay(TIME_FRAME);
    }

    delay(TIME_FRAME);
}

int stUART::receive()
{
    stUTIL::setInputPins(stUART::CLOCK_PIN, stUART::DATA_PIN);

    /* Main receive loop stage */
    CLOCK_STATE.CURRENT = digitalRead(CLOCK_PIN);

    clockPulseTimer();
    callSignDetector();

    if (CALL_SIGN.IS_REGISTERED)
        dataBitsCounter();

    CLOCK_STATE.PREVIOUS = CLOCK_STATE.CURRENT;
}

long stUART::clockPulseTimer()
{
    long PULSE_TIME = millis() - TIMER.START;

    if (CLOCK_STATE.CURRENT == CLOCK_STATE.PREVIOUS == HIGH)
    {
        if (!TIMER.IS_STARTED)
        {
            TIMER.START = millis();
            TIMER.IS_STARTED = true;
        }
    }
    else
    {
        if (PULSE_TIME > (stUART::TIME_FRAME * 4))
            CALL_SIGN.IS_CALLED = true;

        TIMER.IS_STARTED = false;
    }

    return PULSE_TIME;
}

void stUART::callSignDetector()
{
    if (CALL_SIGN.IS_CALLED && isTrailingEdgeClock())
    {
        CALL_SIGN.IS_REGISTERED = true;
        CALL_SIGN.IS_CALLED = false;

        if (TEST_ENVIRONMENT)
            Serial.println("<NewDataFrame/>");
    }
}

void stUART::dataBitsCounter()
{

    if (isRisingEdgeClock())
    {
        DATA_FRAME.DONE = false;
        int DATA_BIT = digitalRead(DATA_PIN);
        DATA_FRAME.STORE[DATA_FRAME.COUNTER] = DATA_BIT;
        DATA_FRAME.COUNTER++;
    }

    if (DATA_FRAME.COUNTER == 8)
    {
        DATA_FRAME.DONE = true;          // PACK UP SIGNAL
        DATA_FRAME.COUNTER = 0;          // RESET
        CALL_SIGN.IS_REGISTERED = false; // CLOSE READ

        if (TEST_ENVIRONMENT)
        {
            for (int i = 0; i < 8; i++)
            {
                Serial.print(DATA_FRAME.STORE[i]);
            }
            Serial.println("");
        }
    }
}

bool stUART::isTrailingEdgeClock()
{
    return CLOCK_STATE.PREVIOUS == HIGH && CLOCK_STATE.CURRENT == LOW;
}

bool stUART::isRisingEdgeClock()
{
    return CLOCK_STATE.PREVIOUS == LOW && CLOCK_STATE.CURRENT == HIGH;
}