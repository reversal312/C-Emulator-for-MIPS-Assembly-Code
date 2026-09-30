#include <stdint.h>

#define MEM_SIZE 4096
#define MIPS_RAM_BASE 0x00400000u
#define MIPS_RAM_SIZE (1024u * 1024u)
#define MIPS_UART_TX 0xffff0000u
#define MIPS_TIMER 0xffff0010u
#define MIPS_REGISTER_COUNT 32u
#define MIPS_SP_REGISTER 29u

typedef enum
{
    STOP_RUNNING,
    STOP_BREAK,
    STOP_INVALID_INSTRUCTION,
    STOP_MEMORY_FAULT,
    STOP_INSTRUCTION_LIMIT
}StopReason;

typedef struct cpu_t
{
  uint32_t reg[32];
  uint32_t pc;
  uint32_t mem[MEM_SIZE];
  int halted;

  StopReason stop_reason;
  char fault_message[128];

  uint64_t instruction_count;
  uint64_t load_count;
  uint64_t store_count;
  uint64_t branch_count;
  uint64_t mmio_write_count;
}cpu_t;

void cpu_init(cpu_t *c);
void step(cpu_t *c);


