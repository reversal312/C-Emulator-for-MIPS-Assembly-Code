#include "core.h"
#include <stdio.h>

int main()
{
  cpu_t c;

  cpu_init(&c);
  //addi instruction set
  c.mem[0] = 0x20;
  c.mem[1] = 0x08;
  c.mem[2] = 0x00;
  c.mem[3] = 0x05;
  
  step(&c);
  
  printf("%d\n%d\n", c.reg[8], c.pc);

  //break
  c.mem[4] = 0x00;
  c.mem[5] = 0x00;
  c.mem[6] = 0x00;
  c.mem[7] = 0x0d;
  
  step(&c);
  printf("halt = %d, stop = %d", c.halted, c.stop_reason);  


}
