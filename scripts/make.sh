#!/bin/bash

if [[ "$1" == "build" ]]; then
  if [ -d "../program/build" ]; then
    rm -rf ../program/build
  fi

  if command -v ${CH32_DEV}bin/riscv-none-embed-gcc >/dev/null 2>&1; then
    cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -S ../program -B ../program/build
    cmake --build ../program/build --target miniFOC.elf
  else
    echo "gcc is not installed or cannot be used."
    exit 1
  fi
 
elif [[ "$1" == "flash" ]]; then
  elf_file=$(realpath "../program/build/miniFOC.elf")
  cfg_file=$(realpath "../program/wch-riscv.cfg")
  sudo ./openocd-ch32v/bin/openocd -f $cfg_file -c init -c halt -c "program ${elf_file}" -c exit
elif [[ "$1" == "clean" ]]; then
  elf_file=$(realpath "../program/build/miniFOC.elf")
  cfg_file=$(realpath "../program/wch-riscv.cfg")
  sudo ./openocd-ch32v/bin/openocd -f $cfg_file -c init -c halt -c "flash erase_sector wch_riscv 0 last " -c exit 
  rm -rf ../program/build
else
  echo "Usage: $0 [build | flash | clean]"
  exit 1
fi

