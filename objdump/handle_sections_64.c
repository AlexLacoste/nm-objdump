/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.lacoste
** File description:
** handle_sections_64
*/

#include <stdio.h>
#include <string.h>
#include "../include/objdump.h"

// static void display_content(Elf64_Ehdr *elf_ehdr, Elf64_Shdr elfshdr)
// {

// }

void handle_sections_64(Elf64_Ehdr *elf_ehdr, Elf64_Shdr *elf_shdr)
{
    char *cast = (void *)elf_ehdr + elf_shdr[elf_ehdr->e_shstrndx].sh_offset;

    for (int i = 0; i < elf_ehdr->e_shnum; i++) {
        if (elf_shdr[i].sh_name
            && strcmp(cast + elf_shdr[i].sh_name, ".shstrtab") != 0
            && strcmp(cast + elf_shdr[i].sh_name, ".symtab") != 0
            && strcmp(cast + elf_shdr[i].sh_name, ".bss") != 0
            && strcmp(cast + elf_shdr[i].sh_name, ".strtab") != 0) {
            printf("Contents of section %s:\n",
                cast + elf_shdr[i].sh_name); // check si ça marche
            // display_content(elf_ehdr, elf_shdr[i]);
        }
    }
}