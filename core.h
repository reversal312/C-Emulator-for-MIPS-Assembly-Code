#include <stdint.h>

#define MEM_SIZE 4096

typedef struct
{
  uint32_t reg[32];
  uint32_t pc;
  uint32_t mem[MEM_SIZE];
  int halted;
}cpu_t;

void cpu_init(cpu_t *c);
void step(cpu_t *c);
