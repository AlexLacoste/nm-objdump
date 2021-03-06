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

static int check_format(char *file, char *binary, utils_t utils)
{
    if ((FORMAT_EHDR(utils.elf_64, utils.ptr, e_ident[EI_MAG0])) != ELFMAG0
    || (FORMAT_EHDR(utils.elf_64, utils.ptr, e_ident[EI_MAG1])) != ELFMAG1
    || (FORMAT_EHDR(utils.elf_64, utils.ptr, e_ident[EI_MAG2])) != ELFMAG2
    || (FORMAT_EHDR(utils.elf_64, utils.ptr, e_ident[EI_MAG3])) != ELFMAG3) {
        fprintf(stderr, "%s: %s: file format not recognized\n", binary, file);
        return 84;
    }
    return 0;
}

static void print_flag2(utils_t utils, bool check, void *elf_shdr)
{
    for (int i = 0; i < (FORMAT_EHDR(utils.elf_64, utils.ptr, e_shnum)); i++) {
        if ((FORMAT_SHDR(utils.elf_64, elf_shdr, i, sh_type)) == SHT_SYMTAB) {
            if (check)
                printf(", ");
            printf("HAS_SYMS");
            check = true;
            break;
        }
    }
    if ((FORMAT_EHDR(utils.elf_64, utils.ptr, e_type)) == ET_DYN) {
        if (check)
            printf(", ");
        printf("DYNAMIC");
        check = true;
    }
    if ((FORMAT_EHDR(utils.elf_64, utils.ptr, e_phnum)) != 0) {
        if (check)
            printf(", ");
        printf("D_PAGED");
    }
}

static void print_flag(utils_t utils, void *elf_shdr)
{
    bool check = false;

    if ((FORMAT_EHDR(utils.elf_64, utils.ptr, e_type)) == ET_REL) {
        printf("HAS_RELOC");
        check = true;
    }
    if ((FORMAT_EHDR(utils.elf_64, utils.ptr, e_type)) == ET_EXEC) {
        if (check)
            printf(", ");
        printf("EXEC_P");
        check = true;
    }
    print_flag2(utils, check, elf_shdr);
    printf("\n");
}

static void handle_flag(utils_t utils, void *elf_shdr)
{
    unsigned int flag = 0;

    printf("architecture: %s, flags ", utils.elf_64 ? "i386:x86-64" : "i386");
    if ((FORMAT_EHDR(utils.elf_64, utils.ptr, e_type)) == ET_DYN)
        flag |= DYNAMIC;
    if ((FORMAT_EHDR(utils.elf_64, utils.ptr, e_type)) == ET_EXEC)
        flag |= EXEC_P;
    if ((FORMAT_EHDR(utils.elf_64, utils.ptr, e_type)) == ET_REL)
        flag |= HAS_RELOC;
    if ((FORMAT_EHDR(utils.elf_64, utils.ptr, e_phnum)) != 0)
        flag |= D_PAGED;
    for (int i = 0; i < (FORMAT_EHDR(utils.elf_64, utils.ptr, e_shnum)); i++) {
        if ((FORMAT_SHDR(utils.elf_64, elf_shdr, 0, sh_type)) == SHT_SYMTAB)
            flag |= HAS_SYMS;
    }
    printf("0x%08x:\n", flag); // TODO: better handle of flag not good value
    print_flag(utils, elf_shdr);
}

int handle_objdump(char *file, char *binary, utils_t utils)
{
    void *elf_shdr = utils.ptr +
                    (FORMAT_EHDR(utils.elf_64, utils.ptr, e_shoff));

    if (check_format(file, binary, utils) == 84)
        return 84;
    printf("\n%s:     file format %s\n", file, utils.elf_64 ? "elf64-x86-64"
        : "elf32-i386");
    handle_flag(utils, elf_shdr);
    printf("start address 0x%016lx\n\n",
    (FORMAT_EHDR(utils.elf_64, utils.ptr, e_entry)));
    handle_sections(utils, elf_shdr);
    return 0;
}