/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.lacoste
** File description:
** handle_64
*/

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/flags.h"
#include "../include/objdump.h"

static int check_format_64(char *file, char *binary, Elf64_Ehdr *elf_ehdr)
{
    if (elf_ehdr->e_ident[EI_MAG0] != ELFMAG0
        || elf_ehdr->e_ident[EI_MAG1] != ELFMAG1
        || elf_ehdr->e_ident[EI_MAG2] != ELFMAG2
        || elf_ehdr->e_ident[EI_MAG3] != ELFMAG3) {
        fprintf(stderr, "%s: %s: File format not recognized\n", binary, file);
        return 84;
    }
    return 0;
}

static void print_flag2(Elf64_Ehdr *elf_ehdr, Elf64_Shdr *elf_shdr, bool check)
{
    for (int i = 0; i < elf_ehdr->e_shnum; i++) {
        if (elf_shdr[i].sh_type == SHT_SYMTAB) {
            if (check)
                write(1, ", ", 2);
            write(1, "HAS_SYMS", 8);
            check = true;
            break;
        }
    }
    if (elf_ehdr->e_type == ET_DYN) {
        if (check)
            write(1, ", ", 2);
        write(1, "DYNAMIC", 7);
        check = true;
    }
    if (elf_ehdr->e_phnum != 0) {
        if (check)
            write(1, ", ", 2);
        write(1, "D_PAGED", 7);
    }
}

static void print_flag(Elf64_Ehdr *elf_ehdr, Elf64_Shdr *elf_shdr)
{
    bool check = false;

    if (elf_ehdr->e_type == ET_REL) {
        write(1, "HAS_RELOC", 9);
        check = true;
    }
    if (elf_ehdr->e_type == ET_EXEC) {
        if (check)
            write(1, ", ", 2);
        write(1, "EXEC_P", 6);
        check = true;
    }
    print_flag2(elf_ehdr, elf_shdr, check);
    printf("\n");
}

static void handle_flag(Elf64_Ehdr *elf_ehdr, Elf64_Shdr *elf_shdr)
{
    unsigned int flag = 0;

    write(1, "architecture: i386:x86-64, flags ", 33);
    if (elf_ehdr->e_type == ET_DYN)
        flag |= DYNAMIC;
    if (elf_ehdr->e_type == ET_EXEC)
        flag |= EXEC_P;
    if (elf_ehdr->e_type == ET_REL)
        flag |= HAS_RELOC;
    if (elf_ehdr->e_phnum != 0)
        flag |= D_PAGED;
    for (int i = 0; i < elf_ehdr->e_shnum; i++) {
        if (elf_shdr[i].sh_type == SHT_SYMTAB)
            flag |= HAS_SYMS;
    }
    printf("0x%08x:\n", flag);
    print_flag(elf_ehdr, elf_shdr);
}

int handle_64(char *file, char *binary, void *tmp, utils_t utils)
{
    Elf64_Ehdr *elf_ehdr = tmp; // peut être il faudra cast
    Elf64_Shdr *elf_shdr = tmp
        + elf_ehdr->e_shoff; // peut être il faudra cast; pointe sur le header

    (void)utils; //
    if (check_format_64(file, binary, elf_ehdr) == 84)
        return 84;
    // TODO: check truncated
    printf("\n%s:     file format elf64-x86-64\n", file);
    handle_flag(elf_ehdr, elf_shdr);
    printf("start address 0x%016lx\n\n", elf_ehdr->e_entry);
    return 0;
}