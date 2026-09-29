#include "core.h"
#include <stdio.h>

int main()
{
  cpu_t c;

  cpu_init(&c);

  c.mem[0] = 0x20;
  c.mem[1] = 0x08;
  c.mem[2] = 0x00;
  c.mem[3] = 0x05;
  
  step(&c);
}
