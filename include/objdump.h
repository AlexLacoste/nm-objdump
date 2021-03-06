/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.lacoste
** File description:
** objdump
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include <elf.h>
#include <stdbool.h>
#include <sys/types.h>

#define FORMAT_EHDR(format_64, pointer, name) \
(format_64) ? ((Elf64_Ehdr *)pointer)->name : ((Elf32_Ehdr *)pointer)->name

#define FORMAT_SHDR(format_64, pointer, i, name) \
(format_64) ? ((Elf64_Shdr *)pointer)[i].name : ((Elf32_Shdr *)pointer)[i].name

typedef struct utils_s {
    int fd;
    bool elf_64;
    void *ptr;
} utils_t;

int my_objdump(char *file, char *binary);
int print_help(char *binary);

int handle_objdump(char *file, char *binary, utils_t utils);
void handle_sections(utils_t utils, void *elf_shdr);

#endif /* !OBJDUMP_H_ */
