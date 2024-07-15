target remote localhost:3333
set disassemble-next-line on
set logging on
monitor halt
load ../image.elf
file ../image.elf
b main
set $sp = vectors[0]
set $pc = vectors[1]
#monitor reset halt
