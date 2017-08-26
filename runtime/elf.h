//===-- llvm/Support/ELF.h - ELF constants and data structures --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This header contains common, non-processor-specific data structures and
// constants for the ELF file format.
//
// The details of the ELF32 bits in this file are largely based on the Tool
// Interface Standard (TIS) Executable and Linking Format (ELF) Specification
// Version 1.2, May 1995. The ELF64 stuff is based on ELF-64 Object File Format
// Version 1.5, Draft 2, May 1998 as well as OpenBSD header files.
//
//===----------------------------------------------------------------------===//

// BEGIN android-changed
#ifndef ART_RUNTIME_ELF_H_
#define ART_RUNTIME_ELF_H_
// END android-changed

// BEGIN android-changed
#include <stdint.h>
#include <string.h>
// END android-changed
#include <sys/elf.h>

typedef uint32_t Elf32_Addr; // Program address
typedef uint32_t Elf32_Off;  // File offset
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Word;
typedef int32_t  Elf32_Sword;

typedef uint64_t Elf64_Addr;
typedef uint64_t Elf64_Off;
typedef uint16_t Elf64_Half;
typedef uint32_t Elf64_Word;
typedef int32_t  Elf64_Sword;
typedef uint64_t Elf64_Xword;
typedef int64_t  Elf64_Sxword;

// Object file magic string.
static constexpr char ElfMagic[] = { 0x7f, 'E', 'L', 'F', '\0' };

// Mips Specific e_flags
enum : unsigned {
  EF_MIPS_NOREORDER = 0x00000001, // Don't reorder instructions
  EF_MIPS_PIC       = 0x00000002, // Position independent code
  EF_MIPS_CPIC      = 0x00000004, // Call object with Position independent code
  EF_MIPS_ABI2      = 0x00000020,
  EF_MIPS_32BITMODE = 0x00000100,
  EF_MIPS_NAN2008   = 0x00000400, // Uses IEE 754-2008 NaN encoding
  EF_MIPS_ABI_O32   = 0x00001000, // This file follows the first MIPS 32 bit ABI

  //ARCH_ASE
  EF_MIPS_MICROMIPS = 0x02000000, // microMIPS
  EF_MIPS_ARCH_ASE_M16 =
                      0x04000000, // Has Mips-16 ISA extensions
  //ARCH
  EF_MIPS_ARCH_1    = 0x00000000, // MIPS1 instruction set
  EF_MIPS_ARCH_2    = 0x10000000, // MIPS2 instruction set
  EF_MIPS_ARCH_3    = 0x20000000, // MIPS3 instruction set
  EF_MIPS_ARCH_4    = 0x30000000, // MIPS4 instruction set
  EF_MIPS_ARCH_5    = 0x40000000, // MIPS5 instruction set
  EF_MIPS_ARCH_32   = 0x50000000, // MIPS32 instruction set per linux not elf.h
  EF_MIPS_ARCH_64   = 0x60000000, // MIPS64 instruction set per linux not elf.h
  EF_MIPS_ARCH_32R2 = 0x70000000, // mips32r2
  EF_MIPS_ARCH_64R2 = 0x80000000, // mips64r2
  EF_MIPS_ARCH_32R6 = 0x90000000, // mips32r6
  EF_MIPS_ARCH_64R6 = 0xa0000000, // mips64r6
  EF_MIPS_ARCH      = 0xf0000000  // Mask for applying EF_MIPS_ARCH_ variant
};

enum {
  EM_AARCH64       = 183, // ARM AArch64
};

struct ElfTypes32 {
  typedef Elf32_Addr Addr;
  typedef Elf32_Off Off;
  typedef Elf32_Half Half;
  typedef Elf32_Word Word;
  typedef Elf32_Sword Sword;
  typedef Elf32_Ehdr Ehdr;
  typedef Elf32_Shdr Shdr;
  typedef Elf32_Sym Sym;
  typedef Elf32_Rel Rel;
  typedef Elf32_Rela Rela;
  typedef Elf32_Phdr Phdr;
  typedef Elf32_Dyn Dyn;
};

struct ElfTypes64 {
  typedef Elf64_Addr Addr;
  typedef Elf64_Off Off;
  typedef Elf64_Half Half;
  typedef Elf64_Word Word;
  typedef Elf64_Sword Sword;
  typedef Elf64_Xword Xword;
  typedef Elf64_Sxword Sxword;
  typedef Elf64_Ehdr Ehdr;
  typedef Elf64_Shdr Shdr;
  typedef Elf64_Sym Sym;
  typedef Elf64_Rel Rel;
  typedef Elf64_Rela Rela;
  typedef Elf64_Phdr Phdr;
  typedef Elf64_Dyn Dyn;
};

// BEGIN android-changed
#endif  // ART_RUNTIME_ELF_H_
// END android-changed
