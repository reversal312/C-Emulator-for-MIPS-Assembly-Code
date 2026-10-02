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
  uint32_t rd = instruction >> 11 & 0x1f;
  uint32_t imm = instruction & 0xffff;
  uint32_t shamt = instruction >> 6 & 0x1f; 
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
  if(funct == 0x0d)
  {
    c->halted = 1;
    c->stop_reason = STOP_BREAK;
  }
  // R-type Add
  if(funct == 0x20)
  {
    if(rd != 0)
      c->reg[rd] = c->reg[rt] + c->reg[rs];
  }
  //R-type sub
  if(funct == 0x22)
  {
    if(rd != 0)
      c->reg[rd] = c->reg[rs] - c->reg[rt];
  }
  //slt
  if(funct == 0x2A)
  {
    if(rd != 0)
      if((int32_t)c->reg[rs] < (int32_t)c->reg[rt])
        c->reg[rd] = 1;
      else 
        c->reg[rd] = 0;
  }
  //and 
  if(funct == 0x24)
    if(rd != 0)
      c->reg[rd] = c->reg[rs] & c-> reg[rt];
  //or 
  if(funct == 0x25)
    if(rd != 0)
      c->reg[rd] = c->reg[rs] | c->reg[rt];
  //andi  
  if(opcode == 0x0c)
    if(rt != 0)
      c->reg[rt] = c->reg[rs] & imm;
  //ori 
  if(opcode == 0x0d)
    if(rt != 0)
      c->reg[rt] = c->reg[rs] | imm;
  //sll 
  if(funct == 0x00)
    if(rd != 0)
      c->reg[rd] = c->reg[rt] << shamt;
  //srl 
  if(funct == 0x02)
  {
    if(rd != 0)
      c->reg[rd] = c->reg[rt] >> shamt;
  }
  // lw

  if(opcode == 0x23)
  {
    uint32_t addr = c->reg[rs] + imm16;
    uint32_t word;
    if(addr % 4 != 0 || addr > RAM_SIZE - 4)
    {
      c->halted = 1;
      c->stop_reason = STOP_MEMORY_FAULT;
      return;
    }
    word = ((uint32_t)c->mem[addr]   << 24) |
         ((uint32_t)c->mem[addr+1] << 16) |
         ((uint32_t)c->mem[addr+2] << 8)  |
          (uint32_t)c->mem[addr+3];
    if(rt != 0)
      c->reg[rt] = word;
  }

  c->pc += 4;
}

