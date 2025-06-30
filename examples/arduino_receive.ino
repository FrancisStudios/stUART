#include <stuart.h>
int DATA_FRAME, DATA_FRAME_DONE_SIGNAL;

void setup() {
  Serial.begin(9600);
  stUART::begin(100, 6, 5);
}

void loop() {
  stUART::receive(DATA_FRAME, DATA_FRAME_DONE_SIGNAL);
}
