#include <stdio.h>
#include <string.h>

#include "cpu.h"
#include "memory.h"
#include "registers.h"
#include "rom.h"

int main(int argc, char **argv) {
  char *filename = NULL;

  printf("CHIP-8 Simple Disassembler - A1\n");

  if (argc != 2) {
    printf("Wrong arguments.\nUsage: %s <path-to-rom>\n", argv[0]);
    return -1;
  }

  filename = argv[1];
  if (filename == NULL) {
    printf("Bad input.\nUsage: %s <path-to-rom>\n", argv[0]);
    return -1;
  }

  reset();

  printf("Loading \"%s\"\n", filename);

  int16_t rom_size = load_rom(filename);
  if (rom_size <= 0) {
    printf("Unable to load \"%s\"\n", filename);
    return -1;
  }

  printf("Done\n");

  while (registers.PC < rom_size + 0x200) {
    cpu_step();
  };

  return 0;
}