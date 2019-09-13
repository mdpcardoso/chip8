#include <stdio.h>

#include "memory.h"

#include "rom.h"

int16_t load_rom(const char *filename) {
  FILE *fp;
  fp = fopen(filename, "rb");

  if (NULL == fp) {
    return -1;
  }

  fseek(fp, 0, SEEK_END); // seek to end of file
  long size = ftell(fp);  // get current file pointer
  rewind(fp);

  if (size >= MAX_ROM_SIZE) {
    fclose(fp);
    return -1;
  }

  if (fread(ram + 0x200, sizeof(ram[0]), size, fp) != size) {
    fclose(fp);
    return -1;
  }

  fclose(fp);

  return size;
}