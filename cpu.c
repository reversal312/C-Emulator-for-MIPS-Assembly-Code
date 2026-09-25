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

  c->pc += 4;
}

