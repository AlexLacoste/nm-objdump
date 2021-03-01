/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.lacoste
** File description:
** objdump
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include <elf.h>
#include <sys/types.h>

typedef struct utils_s {
    int fd;
    off_t size;
} utils_t;

int my_objdump(char *file, char *binary);
int print_help(char *binary);
int handle_64(char *file, char *binary, void *tmp, utils_t utils);
void handle_sections_64(Elf64_Ehdr *elf_ehdr, Elf64_Shdr *elf_shdr);

#endif /* !OBJDUMP_H_ */
