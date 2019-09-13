# CHIP-8
A simple CHIP-8 disassembler.

## Building And Usage
> make  
> chip8 \<path-to-rom>

## Sample Output
> Chip-8 Simple Disassembler - A1  
> Loading "rom/sample.rom"  
> Done  
> LD      V0, 0x00  
> LD      V1, 0x00  
> LD      I, 0x222  
> RND     V2, 0x01  
> SE      V2, 0x01  
> LD      I, 0x21e  
> DRW     V0, V1, 0x4  
> ...  