/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** nm
*/

#ifndef NM_H_
#define NM_H_

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

int my_nm(char *file, char *binary);
int print_help(char *binary);

int handle_nm(char *file, char *binary, utils_t utils);

#endif /* !NM_H_ */
