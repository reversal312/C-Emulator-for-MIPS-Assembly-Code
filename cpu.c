#include "core.h"
#include <string.h>
#include <stdio.h>


void cpu_init(cpu_t *c)
{
  memset(c, 0, sizeof(cpu_t));
}

void step(cpu_t *c)
{
  uint32_t by0 = c->mem[c->pc];
  uint32_t by1 = c->mem[c->pc+1];
  uint32_t by2 = c->mem[c->pc+2];
  uint32_t by3 = c->mem[c->pc+3];

  uint32_t instruction = (by0 << 24) | (by1 << 16) | (by2 << 8) | by3;

  printf("pc=%08x instruction=%08x\n", c->pc, instruction);

  uint32_t funct = instruction & 0x3f;
  uint32_t opcode = instruction >> 26;
  uint32_t rs = instruction >> 21 & 0x1f;
  uint32_t rt = instruction >> 16 & 0x1f;
  uint32_t imm = instruction & 0xffff;
 
  int32_t imm16 = (int32_t)(int16_t)imm;
  // Addi instruction
  if(opcode == 0x08)
  {
    int32_t temp = c->reg[rs] + imm16;
  
    if(rt != 0)
      c->reg[rt] = temp;
  }
  c->reg[0] = 0;
  
  //break instruction
  if(opcode == 0 && funct == 0x0d)
  {
    c->halted = 1;
    c->stop_reason = STOP_BREAK;
  }


  c->pc += 4;
}

