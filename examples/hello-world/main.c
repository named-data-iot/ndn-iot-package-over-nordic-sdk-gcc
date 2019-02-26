#include "stdio.h"
#include "platform/system.h"

int main()
{
  printf("Hello in NDN Lite Example: Hello World\n");
  ndn_platform_init();
  while(1)
  {
    ndn_platform_delay_ms(500);
    printf("NDN Lite: current system time: %d ms\n", (int)ndn_platform_current_time());
  }
}
