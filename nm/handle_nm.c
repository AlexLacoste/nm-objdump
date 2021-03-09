/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** handle_nm
*/

#include "../include/nm.h"

int handle_nm(char *file, char *binary, utils_t utils)
{
    void *elf_shdr = utils.ptr +
                    (FORMAT_EHDR(utils.elf_64, utils.ptr, e_shoff));

    for (int i = 0; i < (FORMAT_EHDR(utils.elf_64, utils.ptr, e_shnum)); i++) {
        if ((FORMAT_SHDR(utils.elf_64, elf_shdr, i, sh_type)) == SHT_SYMTAB) {

        }
    }
    return 0;
}