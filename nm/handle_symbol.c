/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** handle_type
*/

#include <stdio.h>
#include "../include/nm.h"

static char set_symbol3(utils_t utils, int offset)
{
    if (FORMAT_SHDR(utils.elf_64, utils.shdr, FORMAT_SYM(utils.elf_64,
    utils.sym, st_shndx), sh_type) == SHT_PROGBITS && FORMAT_SHDR(utils.elf_64,
    utils.shdr, FORMAT_SYM(utils.elf_64, utils.sym, st_shndx), sh_flags) ==
    (SHF_ALLOC | SHF_EXECINSTR))
        return 'T' + offset;
    if (FORMAT_SHDR(utils.elf_64, utils.shdr, FORMAT_SYM(utils.elf_64,
    utils.sym, st_shndx), sh_type) == SHT_PROGBITS && FORMAT_SHDR(utils.elf_64,
    utils.shdr, FORMAT_SYM(utils.elf_64, utils.sym, st_shndx), sh_flags) ==
    (SHF_ALLOC))
        return 'r';
    if (FORMAT_SHDR(utils.elf_64, utils.shdr, FORMAT_SYM(utils.elf_64,
    utils.sym, st_shndx), sh_type) == SHT_PROGBITS)
        return 'N';
    return '?';
}

static char set_symbol2(utils_t utils, int offset)
{
    if ((FORMAT_SHDR(utils.elf_64,
    utils.shdr, FORMAT_SYM(utils.elf_64, utils.sym, st_shndx), sh_type) ==
    SHT_NOBITS && FORMAT_SHDR(utils.elf_64, utils.shdr, FORMAT_SYM(
    utils.elf_64, utils.sym, st_shndx), sh_flags) == (SHF_ALLOC | SHF_WRITE)))
        return 'B' + offset;
    if ((FORMAT_SHDR(utils.elf_64, utils.shdr, FORMAT_SYM(utils.elf_64,
    utils.sym, st_shndx), sh_type) == SHT_PROGBITS && FORMAT_SHDR(utils.elf_64,
    utils.shdr, FORMAT_SYM(utils.elf_64, utils.sym, st_shndx), sh_flags) ==
    (SHF_ALLOC | SHF_WRITE)) || FORMAT_SHDR(utils.elf_64, utils.shdr,
    FORMAT_SYM(utils.elf_64, utils.sym, st_shndx), sh_type) == SHT_DYNAMIC ||
    FORMAT_SHDR(utils.elf_64, utils.shdr, FORMAT_SYM(utils.elf_64, utils.sym,
    st_shndx), sh_type) == SHT_INIT_ARRAY || FORMAT_SHDR(utils.elf_64,
    utils.shdr, FORMAT_SYM(utils.elf_64, utils.sym, st_shndx), sh_type) ==
    SHT_FINI_ARRAY)
        return 'D' + offset;
    return set_symbol3(utils, offset);
}

char set_symbol(unsigned char st_type, int st_bind, utils_t utils)
{
    int offset = (st_bind == STB_LOCAL) ? 32 : 0;

    if (FORMAT_SYM(utils.elf_64, utils.sym, st_shndx) == STB_GNU_UNIQUE)
        return 'u';
    if (st_bind == STB_WEAK) {
        if (st_type == STT_OBJECT)
            return (FORMAT_SYM(utils.elf_64, utils.sym, st_shndx) ==
            SHN_UNDEF) ? 'v': 'V';
        else
            return (FORMAT_SYM(utils.elf_64, utils.sym, st_shndx) ==
            SHN_UNDEF) ? 'w': 'W';
    }
    if ((FORMAT_SYM(utils.elf_64, utils.sym, st_shndx) == SHN_UNDEF))
        return 'U';
    if (FORMAT_SYM(utils.elf_64, utils.sym, st_shndx) == SHN_ABS)
        return 'A' + offset;
    if (FORMAT_SYM(utils.elf_64, utils.sym, st_shndx) == SHN_COMMON)
        return 'C';
    return set_symbol2(utils, offset);
}