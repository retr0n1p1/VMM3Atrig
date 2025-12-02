#!/bin/bash
rm kuku.bin
make clean
make "VMM3A FEB v1.0.elf" -j4
arm-none-eabi-objcopy -O binary VMM3A\ FEB\ v1.0.elf kuku.bin
