#include <stuart.h>

void setup()
{
  stUART::begin(100, 6, 5);
}

void loop()
{
  int message[4] = {1, 2, 3, 4};

  for (int i = 0; i < 4; i++)
  {
    if (stUART::transmit())
      stUART::transmit(message[i]);
  }
}
