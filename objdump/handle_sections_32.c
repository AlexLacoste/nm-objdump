/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.lacoste
** File description:
** handle_sections_32
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../include/objdump.h"

static void display_hexa(
    Elf32_Ehdr *elf_ehdr, Elf32_Shdr elf_shdr, size_t rest)
{
    bool check_end = false;
    size_t i = 0;

    for (; i < 16; i++) {
        if (i % 4 == 0)
            printf(" ");
        if (i >= rest) {
            (i % 4 != 0 && elf_shdr.sh_size - rest + 16 >= elf_shdr.sh_size)
                ? printf(" ")
                : 0;
            check_end = true;
            break;
        } printf("%02x",
            (unsigned char)((char *)elf_ehdr
                + elf_shdr.sh_offset)[elf_shdr.sh_size - rest + i]);
    } if (check_end) {
        for (; i < 16; i++)
            (i % 4 == 0) ? printf("   ") : printf("  ");
    }
    (check_end) ? printf(" ") : printf("  ");
}

static void display_ascii(
    Elf32_Ehdr *elf_ehdr, Elf32_Shdr elf_shdr, size_t rest)
{
    bool check_end = false;
    size_t i = 0;
    unsigned char c = '\0';

    for (; i < 16; i++) {
        if (i >= rest) {
            check_end = true;
            break;
        }
        c = (unsigned char)((char *)elf_ehdr
            + elf_shdr.sh_offset)[elf_shdr.sh_size - rest + i];
        if (c >= 32 && c <= 126)
            printf("%c", c);
        else
            printf(".");
    }
    if (check_end) {
        for (; i < 16; i++)
            printf(" ");
    }
}

static void display_content(Elf32_Ehdr *elf_ehdr, Elf32_Shdr elf_shdr)
{
    for (size_t i = 0; i < elf_shdr.sh_size; i += 16) {
        printf(" %04lx", i + elf_shdr.sh_addr);
        display_hexa(elf_ehdr, elf_shdr, elf_shdr.sh_size - i);
        display_ascii(elf_ehdr, elf_shdr, elf_shdr.sh_size - i);
        printf("\n");
    }
}

void handle_sections_32(Elf32_Ehdr *elf_ehdr, Elf32_Shdr *elf_shdr)
{
    char *cast = (void *)elf_ehdr + elf_shdr[elf_ehdr->e_shstrndx].sh_offset;

    for (int i = 0; i < elf_ehdr->e_shnum; i++) {
        if (elf_shdr[i].sh_name
            && strcmp(cast + elf_shdr[i].sh_name, ".shstrtab") != 0
            && strcmp(cast + elf_shdr[i].sh_name, ".symtab") != 0
            && strcmp(cast + elf_shdr[i].sh_name, ".bss") != 0
            && strcmp(cast + elf_shdr[i].sh_name, ".strtab") != 0) {
            printf("Contents of section %s:\n", cast + elf_shdr[i].sh_name);
            display_content(elf_ehdr, elf_shdr[i]);
        }
    }
}