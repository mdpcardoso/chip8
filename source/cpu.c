#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "registers.h"

#include "cpu.h"

const struct instruction instructions[34] = {
    {"CLS", 0xFFFF, 0x00E0, NULL, NULL},
    {"RET", 0xFFFF, 0x00EE, NULL, NULL},
    {"JMP\t0x%04x", 0xF000, 0x1000, decode_nnn, NULL},
    {"CALL\t0x%04x", 0xF000, 0x2000, decode_nnn, NULL},
    {"SE\tV%d, 0x%02x", 0xF000, 0x3000, decode_xkk, NULL},
    {"SNE\tV%d, 0x%02x", 0xF000, 0x4000, decode_xkk, NULL},
    {"SE\tV%d, V%d", 0xF00F, 0x5000, decode_xy0, NULL},
    {"LD\tV%d, 0x%02x", 0xF000, 0x6000, decode_xkk, NULL},
    {"ADD\tV%d, 0x%02x", 0xF000, 0x7000, decode_xkk, NULL},
    {"LD\tV%d, V%d", 0xF00F, 0x8000, decode_xy0, NULL},
    {"OR\tV%d, V%d", 0xF00F, 0x8001, decode_xy0, NULL},
    {"AND\tV%d, V%d", 0xF00F, 0x8002, decode_xy0, NULL},
    {"XOR\tV%d, V%d", 0xF00F, 0x8003, decode_xy0, NULL},
    {"ADD\tV%d, V%d", 0xF00F, 0x8004, decode_xy0, NULL},
    {"SUB\tV%d, V%d", 0xF00F, 0x8005, decode_xy0, NULL},
    {"SHR\tV%d {, V%d}", 0xF00F, 0x8006, decode_xy0, NULL},
    {"SUBN\tV%d, V%d", 0xF00F, 0x8007, decode_xy0, NULL},
    {"SHL\tV%d {, V%d}", 0xF00F, 0x800E, decode_xy0, NULL},
    {"SNE\tV%d, V%d", 0xF00F, 0x9000, decode_xy0, NULL},
    {"LD\tI, 0x%02x", 0xF000, 0xA000, decode_nnn, NULL},
    {"JP\tV0, 0x%04x", 0xF000, 0xB000, decode_nnn, NULL},
    {"RND\tV%d, 0x%02x", 0xF000, 0xC000, decode_xkk, NULL},
    {"DRW\tV%d, V%d, 0x%01x", 0xF000, 0xD000, decode_xyn, NULL},
    {"SKP\tV%d", 0xF0FF, 0xE09E, decode_x00, NULL},
    {"SKNP\tV%d", 0xF0FF, 0xE0A1, decode_x00, NULL},
    {"LD\tV%d, DT", 0xF0FF, 0xF007, decode_x00, NULL},
    {"LD\tV%d, K", 0xF0FF, 0xF00A, decode_x00, NULL},
    {"LD\tDT, V%d", 0xF0FF, 0xF015, decode_x00, NULL},
    {"LD\tST, V%d", 0xF0FF, 0xF018, decode_x00, NULL},
    {"ADD\tI, V%d", 0xF0FF, 0xF01E, decode_x00, NULL},
    {"LD\tF, V%d", 0xF0FF, 0xF029, decode_x00, NULL},
    {"LD\tV, V%d", 0xF0FF, 0xF033, decode_x00, NULL},
    {"LD\t[I], V%d", 0xF0FF, 0xF055, decode_x00, NULL},
    {"LD\tV%d, [I]", 0xF0FF, 0xF065, decode_x00, NULL},
};

uint16_t nnn = 0, n = 0;
uint8_t kk = 0;
uint8_t x = 0, y = 0;
uint8_t *vx = NULL, *vy = NULL;

void cpu_step(void) {
  uint16_t opcode = ram[registers.PC] << 8 | ram[registers.PC + 1];

  registers.PC += 2;

  for (size_t i = 0; i < NUM_OPCODES; i++) {
    if (instructions[i].code == (instructions[i].mask & opcode) &&
        instructions[i].decode != NULL) {

      instructions[i].decode(opcode);

      if (instructions[i].decode == &decode_nnn) {
        printf(instructions[i].disassembly, nnn);
      } else if (instructions[i].decode == &decode_xkk) {
        printf(instructions[i].disassembly, x, kk);
      } else if (instructions[i].decode == &decode_xy0) {
        printf(instructions[i].disassembly, x, y);
      } else if (instructions[i].decode == &decode_xyn) {
        printf(instructions[i].disassembly, x, y, n);
      } else if (instructions[i].decode == &decode_x00) {
        printf(instructions[i].disassembly, x);
      }

      printf("\n");

      return;
    }
  }

  printf("PC: 0x%02x OP: 0x%04x\n", registers.PC, opcode);
}

void decode_nnn(uint16_t opcode) { nnn = opcode & 0x0FFF; }

void decode_xkk(uint16_t opcode) {
  x = (opcode >> 8) & 0xF;
  // vx = &registers.V[x];
  kk = opcode & 0xFF;
}

void decode_xy0(uint16_t opcode) {
  x = (opcode >> 8) & 0xF;
  y = (opcode >> 4) & 0xF;
  // vx = &registers.V[x];
  // vy = &registers.V[y];
}

void decode_xyn(uint16_t opcode) {
  x = (opcode >> 8) & 0xF;
  y = (opcode >> 4) & 0xF;
  // vx = &registers.V[x];
  // vy = &registers.V[y];
  n = opcode & 0xF;
}

void decode_x00(uint16_t opcode) {
  x = (opcode >> 8) & 0xF;
  // vx = &registers.V[x];
}