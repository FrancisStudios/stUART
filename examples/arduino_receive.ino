#include <stuart.h>

void setup() {
  Serial.begin(9600);
  stUART::begin(100, 6, 5);
}

void loop() {
  int result = stUART::receive();
  if (result < 0xFF) Serial.println(result);
}
