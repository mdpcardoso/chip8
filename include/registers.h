#include <stdint.h>

struct registers {
  uint8_t V[0x10];

  uint8_t DT;
  uint8_t ST;

  uint16_t I;
  uint16_t SP;
  uint16_t PC;
} extern registers;
