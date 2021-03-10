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

static const handle_flag_t handle_print_flag[] = {
    {"HAS_RELOC", HAS_RELOC},
    {"EXEC_P", EXEC_P},
    {"HAS_SYMS", HAS_SYMS},
    {"DYNAMIC", DYNAMIC},
    {"D_PAGED", D_PAGED}
};

static void print_flag(unsigned int flag)
{
    bool check = false;

    for (size_t i = 0; i < 5; i++) {
        if (flag & handle_print_flag[i].flag && !check) {
            printf("%s", handle_print_flag[i].display);
            check = true;
        } else if (flag & handle_print_flag[i].flag)
            printf(", %s", handle_print_flag[i].display);
    }
    printf("\n");
}

static void handle_flag(utils_t utils, void *elf_shdr)
{
    unsigned int flag = 0;
    size_t type_sh = 0;

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
        type_sh = (FORMAT_SHDR(utils.elf_64, elf_shdr, i, sh_type));
        if (type_sh == SHT_SYMTAB || type_sh == SHT_GNU_versym || type_sh ==
        SHT_SUNW_syminfo || type_sh == SHT_HASH || type_sh == SHT_DYNSYM)
            flag |= HAS_SYMS;
    } printf("0x%08x:\n", flag);
    print_flag(flag);
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