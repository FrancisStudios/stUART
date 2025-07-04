#include <stuart.h>

void setup() {
  Serial.begin(9600);
  stUART::begin(100, 6, 5);
}

void loop() {
  stUART::receive();
}
