/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.lacoste
** File description:
** objdump
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include "shared.h"

typedef struct handle_flag_s {
    char * const display;
    unsigned int flag;
} handle_flag_t;

int my_objdump(char *file, char *binary);
int print_help(char *binary);

int handle_objdump(char *file, char *binary, utils_t utils);
void handle_sections(utils_t utils, void *elf_shdr);

#endif /* !OBJDUMP_H_ */
