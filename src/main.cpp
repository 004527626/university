/**
 * Copyright 2014 Andrew Brinker, Anthony Sterrett
 */

#include <vm/VirtualMachine.h>
#include <asm/Assembler.h>
#include <cstdio>
#include <cstdlib>
#include <cstdint>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <assembly file name>", argv[0]);
    exit(EXIT_FAILURE);
  }
  Assembler a;
  VirtualMachine vm;
  std::list<uint16_t> result = a.parse(argv[1]);
  vm.run(result);
  return 0;
}
