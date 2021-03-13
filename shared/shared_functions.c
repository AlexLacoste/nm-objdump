/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** shared_functions
*/

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include "../include/shared.h"

int check_format(char *file, char *binary, utils_t utils)
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

int handle_open(char *file, utils_t *utils)
{
    utils->fd = open(file, O_RDONLY);
    if (utils->fd == -1)
        return 84;
    return 0;
}

void *handle_mmap(char *file, char *binary, utils_t utils, size_t size)
{
    void *tmp = NULL;

    tmp = mmap(NULL, size, PROT_READ, MAP_SHARED, utils.fd, 0);
    if (!tmp) {
        close(utils.fd);
        return NULL;
    }
    if ((((Elf64_Ehdr *)tmp)->e_ident[EI_CLASS] != ELFCLASS64 &&
    ((Elf64_Ehdr *)tmp)->e_ident[EI_CLASS] != ELFCLASS32) ||
    ((((Elf64_Ehdr *)tmp)->e_ident[EI_DATA] != ELFDATA2LSB &&
    ((Elf64_Ehdr *)tmp)->e_ident[EI_DATA] != ELFDATA2MSB)) ||
    (((Elf64_Ehdr *)tmp)->e_ident[EI_CLASS] == ELFCLASS64 &&
    ((Elf64_Ehdr *)tmp)->e_shnum * ((Elf64_Ehdr *)tmp)->e_shentsize
    + ((Elf64_Ehdr *)tmp)->e_shoff > size) || (((Elf32_Ehdr *)tmp)->
    e_ident[EI_CLASS] == ELFCLASS32 && ((Elf32_Ehdr *)tmp)->e_shnum *
    ((Elf32_Ehdr *)tmp)->e_shentsize + ((Elf32_Ehdr *)tmp)->e_shoff > size)) {
        fprintf(stderr, "%s: %s: %s\n", binary, file,
        "file format not recognized");
        close(utils.fd);
        return NULL;
    } return tmp;
}

int handle_error(struct stat st, char *file, char *binary, utils_t *utils)
{
    if (S_ISDIR(st.st_mode)) {
        fprintf(
            stderr, "%s: Warning: '%s' %s\n", binary, file, "is a directory");
        return 84;
    }
    if (access(file, F_OK) == -1) {
        fprintf(stderr, "%s: '%s': %s\n", binary, file, "No such file");
        return 84;
    }
    if (handle_open(file, utils) == 84)
        return 84;
    return 0;
}