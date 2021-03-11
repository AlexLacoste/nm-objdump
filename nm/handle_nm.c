/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** handle_nm
*/

#include <elf.h>
#include <stdio.h>
#include "../include/nm.h"

static void print_hexa(utils_t utils, void *symbol)
{
    size_t hexa = (FORMAT_SYM(utils.elf_64, symbol, st_value));
    (hexa == 0 && (FORMAT_SYM(utils.elf_64, symbol, st_shndx)) == SHN_UNDEF) ?
    printf("                ") : printf("%016lx", hexa);
}

static void display_lines(utils_t utils, void *elf_shdr, int idx_shdr)
{
    void *symbol = utils.ptr + (FORMAT_SHDR(utils.elf_64, elf_shdr, idx_shdr,
    sh_offset));
    char *name = NULL;
    int st_type = 0;

    for (size_t i = 0; i < (FORMAT_SHDR(utils.elf_64, elf_shdr, idx_shdr,
    sh_size)) / (FORMAT_SHDR(utils.elf_64, elf_shdr, idx_shdr, sh_entsize));
    i++, symbol += (FORMAT_SHDR(
    utils.elf_64, elf_shdr, idx_shdr, sh_entsize))) {
        name = (char *) utils.ptr + (FORMAT_SHDR(utils.elf_64, elf_shdr,
        FORMAT_SHDR(utils.elf_64, elf_shdr, idx_shdr, sh_link), sh_offset))
        + (FORMAT_SYM(utils.elf_64, symbol, st_name));
        st_type = ELF64_ST_TYPE(FORMAT_SYM(utils.elf_64, symbol, st_info));
        if (st_type != STT_FILE && name[0]) {
            print_hexa(utils, symbol);
            printf(" %c %s\n", set_symbol(st_type,
                ELF64_ST_BIND(FORMAT_SYM(utils.elf_64, symbol, st_info)),
                FORMAT_SYM(utils.elf_64, symbol, st_value)), name);
        }
    }
}

int handle_nm(char *file, char *binary, utils_t utils, int ac)
{
    void *elf_shdr = utils.ptr +
                    (FORMAT_EHDR(utils.elf_64, utils.ptr, e_shoff));
    bool check_symbol = false;

    if (check_format(file, binary, utils) == 84)
        return 84;
    if (ac > 2)
        printf("\n%s:\n", file);
    for (int i = 0; i < (FORMAT_EHDR(utils.elf_64, utils.ptr, e_shnum)); i++) {
        if ((FORMAT_SHDR(utils.elf_64, elf_shdr, i, sh_type)) == SHT_SYMTAB) {
            display_lines(utils, elf_shdr, i);
            check_symbol = true;
        }
    }
    if (!check_symbol)
        printf("%s: %s: %s\n", binary, file, "no symbols");
    return 0;
}
