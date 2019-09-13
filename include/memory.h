#include <stdint.h>

#define RAM_SIZE 0x1000
#define VRAM_SIZE (64 * 32)
#define STACK_SIZE 0x10
#define FONTSET_SIZE 80

extern uint8_t ram[RAM_SIZE];
extern uint8_t vram[VRAM_SIZE];
extern uint16_t stack[STACK_SIZE];

extern const uint8_t fontset[FONTSET_SIZE];

void reset(void);
