/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.lacoste
** File description:
** handle_sections_64
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../include/objdump.h"

static void display_hexa(
    utils_t utils, size_t idx, int idx_shdr, void *elf_shdr)
{
    bool check_end = false;
    size_t i = 0;

    for (; i < 16; i++) {
        if (i % 4 == 0)
            printf(" ");
        if (i >= (FORMAT_SHDR(utils.elf_64, elf_shdr, idx_shdr, sh_size))
        - idx) {
            (i % 4 != 0 && idx + 16 >= (FORMAT_SHDR(utils.elf_64, elf_shdr,
            idx_shdr, sh_size))) ? printf(" ") : 0;
            check_end = true;
            break;
        }
        printf("%02x", (unsigned char)((char *)utils.ptr + (FORMAT_SHDR(
        utils.elf_64, elf_shdr, idx_shdr, sh_offset)))[idx + i]);
    } if (check_end) {
        for (; i < 16; i++)
            (i % 4 == 0) ? printf("   ") : printf("  ");
    }
    (check_end) ? printf(" ") : printf("  ");
}

static void display_ascii(
    utils_t utils, size_t idx, size_t idx_shdr, void *elf_shdr)
{
    bool check_end = false;
    size_t i = 0;
    unsigned char c = '\0';

    for (; i < 16; i++) {
        if (i >= (FORMAT_SHDR(
                utils.elf_64, elf_shdr, idx_shdr, sh_size - idx))) {
            check_end = true;
            break;
        }
        c = (unsigned char)((char *)utils.ptr + (FORMAT_SHDR(
            utils.elf_64, elf_shdr, idx_shdr, sh_offset)))[idx + i];
        (c >= 32 && c <= 126) ? printf("%c", c) : printf(".");
    }
    if (check_end) {
        for (; i < 16; i++)
            printf(" ");
    }
}

static void display_content(utils_t utils, int idx_shdr, void *elf_shdr)
{
    for (size_t i = 0;
    i < (FORMAT_SHDR(utils.elf_64, elf_shdr, idx_shdr, sh_size));
    i += 16) {
        printf(" %04lx",
        i + (FORMAT_SHDR(utils.elf_64, elf_shdr, idx_shdr, sh_addr)));
        display_hexa(utils, i, idx_shdr, elf_shdr);
        display_ascii(utils, i, idx_shdr, elf_shdr);
        printf("\n");
    }
}

void handle_sections(utils_t utils, void *elf_shdr)
{
    char *cast = utils.ptr
        + (FORMAT_SHDR(utils.elf_64, elf_shdr,
            (FORMAT_EHDR(utils.elf_64, utils.ptr, e_shstrndx)), sh_offset));

    for (int i = 0; i < (FORMAT_EHDR(utils.elf_64, utils.ptr, e_shnum)); i++) {
        if ((FORMAT_SHDR(utils.elf_64, elf_shdr, i, sh_name))
            && strcmp(cast + (FORMAT_SHDR(utils.elf_64, elf_shdr, i, sh_name)),
            ".shstrtab") != 0
            && strcmp(cast + (FORMAT_SHDR(utils.elf_64, elf_shdr, i, sh_name)),
            ".symtab") != 0
            && strcmp(cast + (FORMAT_SHDR(utils.elf_64, elf_shdr, i, sh_name)),
            ".bss") != 0
            && strcmp(cast + (FORMAT_SHDR(utils.elf_64, elf_shdr, i, sh_name)),
            ".strtab") != 0) {
            printf("Contents of section %s:\n",
                cast + (FORMAT_SHDR(utils.elf_64, elf_shdr, i, sh_name)));
            display_content(utils, i, elf_shdr);
        }
    }
}