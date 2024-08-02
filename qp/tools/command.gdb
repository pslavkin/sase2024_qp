target remote localhost:3333
set disassemble-next-line on
set logging enabled on
monitor halt
#load /opt/qp/qpc/examples/arm-cm/lpc4337/qk/gnu/dbg/dpp-qk.elf
#load ../blinky/build/blinky.elf
file blinky/build/blinky.elf
#load ../examples/blinky/qk/gnu/dbg/blinky-qk.elf
#file ../examples/blinky/qk/gnu/dbg/blinky-qk.elf
#load ../examples/blinky/qv/gnu/dbg/blinky-qv.elf
#file ../examples/blinky/qv/gnu/dbg/blinky-qv.elf
b main
#set $sp = vectors[0]
#set $pc = vectors[1]
#monitor reset halt
