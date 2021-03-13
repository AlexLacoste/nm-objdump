/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** shared
*/

#ifndef SHARED_H_
#define SHARED_H_

#include <elf.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>

#define FORMAT_EHDR(format_64, pointer, name) \
((format_64) ? ((Elf64_Ehdr *)pointer)->name : ((Elf32_Ehdr *)pointer)->name)

#define FORMAT_SHDR(format_64, pointer, i, name) \
((format_64) ? ((Elf64_Shdr *)pointer)[i].name : \
((Elf32_Shdr *)pointer)[i].name)

#define FORMAT_SYM(format_64, pointer, name) \
((format_64) ? ((Elf64_Sym *)pointer)->name : ((Elf32_Sym *)pointer)->name)

typedef struct utils_s {
    int fd;
    bool elf_64;
    void *ptr;
    void *shdr;
    void *sym;
} utils_t;

int check_format(char *file, char *binary, utils_t utils);
int handle_open(char *file, utils_t *utils);
void *handle_mmap(char *file, char *binary, utils_t utils, size_t size);
int handle_error(struct stat st, char *file, char *binary, utils_t *utils);

#endif /* !SHARED_H_ */
