#!/bin/bash
rm kuku.bin
make clean
make "VMM3Atrig.elf" -j4
arm-none-eabi-objcopy -O binary VMM3Atrig.elf kuku.bin
