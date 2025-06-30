/**
 *  ------ [ Property of Francis Studios ] ------
 * ==============================================
 * .. github:https://github.com/francisstudios ..
 * ____ ©2025 Francis Studios Softwares by L. ___
 */

#include "stuart.h"
#include "util.h"

/* Variables for comm interface */
int stUART::TIME_FRAME = 0;
int stUART::CLOCK_PIN = 0;
int stUART::DATA_PIN = 0;

/* Variables for receive */
long CLOCK_TIMER_BEGIN_TIMESTAMP = 0; // MILLIS()
bool TIMER_STARTED = false;           // TIMESTAMP SET
bool PREVIOUS_CLOCK_STATUS = false;   // HIGH / LOW
int DATA_BITS_COUNTER = 0;            // COUNT 8 BITS
bool READ_NEW_DATA_FRAME = false;     // IF CALLSIGN IS RECEIVED
int DATA_FRAME_STORE[8];              // DATA FRAME BITS STORE
bool DATA_FRAME_DONE = false;         // FLAG

bool TEST_ENVIRONMENT = true;

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

int stUART::receive(int DATA_FRAME, bool DATA_FRAME_DONE_SIGNAL)
{
    pinMode(CLOCK_PIN, INPUT);
    pinMode(DATA_PIN, INPUT);

    /* Main receive loop stage */
    bool CURRENT_CLOCK_STATUS = digitalRead(CLOCK_PIN);

    clockOnTimer(CURRENT_CLOCK_STATUS, PREVIOUS_CLOCK_STATUS);
    if (READ_NEW_DATA_FRAME)
        dataBitsCounter(CURRENT_CLOCK_STATUS, PREVIOUS_CLOCK_STATUS);

    if (DATA_FRAME_DONE)
    {
        DATA_FRAME = DATA_FRAME_STORE;
        DATA_FRAME_DONE_SIGNAL = DATA_FRAME_DONE;
        return DATA_FRAME_STORE;
    }

    PREVIOUS_CLOCK_STATUS = CURRENT_CLOCK_STATUS;
}

void stUART::clockOnTimer(bool CURRENT_CLOCK_STATUS, bool PREVIOUS_CLOCK_STATUS)
{
    /* Timing clock signal lengths */
    if (CURRENT_CLOCK_STATUS == PREVIOUS_CLOCK_STATUS == HIGH)
    {
        /* Starting timer */
        if (!TIMER_STARTED)
        {
            CLOCK_TIMER_BEGIN_TIMESTAMP = millis();
            TIMER_STARTED = true;
        }
    }
    else
    {
        /* Resetting timer */
        if (millis() - CLOCK_TIMER_BEGIN_TIMESTAMP > (stUART::TIME_FRAME * 4)) // THIS MEANS THAT CALL SIGN IS DONE
        {
            READ_NEW_DATA_FRAME = true;
            if (TEST_ENVIRONMENT)
                Serial.println("<NewDataFrame/>");
        }

        TIMER_STARTED = false; // RESET ANYWAYS
    }
}

void stUART::dataBitsCounter(bool CURRENT_CLOCK_STATUS, bool PREVIOUS_CLOCK_STATUS)
{

    if (PREVIOUS_CLOCK_STATUS == 0 && CURRENT_CLOCK_STATUS == 1) // IF SQA. WAVE LEADING EDGE STARTS
    {
        DATA_FRAME_DONE = false;
        int DATA_BIT = digitalRead(DATA_PIN);
        DATA_FRAME_STORE[DATA_BITS_COUNTER] = DATA_BIT;
        DATA_BITS_COUNTER++;
    }

    if (DATA_BITS_COUNTER == 8)
    {
        DATA_FRAME_DONE = true;      // PACK UP SIGNAL
        DATA_BITS_COUNTER = 0;       // RESET
        READ_NEW_DATA_FRAME = false; // CLOSE READ

        if (TEST_ENVIRONMENT)
        {
            for (int i = 0; i < 8; i++)
            {
                Serial.print(DATA_FRAME_STORE[i]);
            }
            Serial.println("");
        }
    }
}

/**
 * 
 * THERE IS STILL SOME ISSUE WITH THIS.
 * FOR THE FIRST RECEIVED MESSAGE IT WORKS PERFECTLY
 * EVERYONE AFTER THAT IS SHIFTED RIGHT, FOR SOME REASON
 * IT PUTS A ZERO AT THE MSB
 */