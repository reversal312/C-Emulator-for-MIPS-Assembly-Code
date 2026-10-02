#include "core.h"
#include <stdio.h>

int main()
{
  cpu_t c;

  cpu_init(&c);
  
  uint32_t instruction_memory[] = {0x2008000C,0x000848C0,0x00095082,0x0000000D};
  //memory to cpu optimization
  size_t instruction_length = sizeof(instruction_memory) / sizeof(instruction_memory[0]);
  for(uint32_t i=0; i < instruction_length; i++)
  {
    c.mem[i*4] = instruction_memory[i] >> 24;
    c.mem[i*4+1] = instruction_memory[i] >> 16;
    c.mem[i*4+2] = instruction_memory[i] >> 8;
    c.mem[i*4+3] = instruction_memory[i];
  }

  for(uint32_t i=0; i < instruction_length; i++)
    step(&c);

  printf("reg8=%d reg9=%d reg10=%d pc=%d\n", c.reg[8],c.reg[9], c.reg[10], c.pc);

  //printf("reg10=%d reg11=%d reg12=%d reg13=%d pc=%d\n", c.reg[10],c.reg[11], c.reg[12],c.reg[13], c.pc);
  printf("halt = %d, stop = %d\n", c.halted, c.stop_reason);
  printf("%d\n", c.reg[0]);


}
