#include <stdint.h>

#define NUM_OPCODES 34

struct instruction {
  char *disassembly;
  uint16_t mask;
  uint16_t code;
  // unsigned char operand_length;
  const void (*decode)(uint16_t op);
  void (*execute)(void);
} extern const instructions[34];

void cpu_step(void);

void undefined(void);

void decode_nnn(uint16_t opcode);
void decode_xkk(uint16_t opcode);
void decode_xy0(uint16_t opcode);
void decode_xyn(uint16_t opcode);
void decode_x00(uint16_t opcode);