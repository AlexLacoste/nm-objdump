/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** my_nm
*/

#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../include/nm.h"

int my_nm(char *file, char *binary)
{
    utils_t utils = {.fd = 0, .elf_64 = false};
    int ret = 0;
    struct stat st;

    if (stat(file, &st) == -1) {
        fprintf(stderr, "%s: '%s': %s\n", binary, file, "No such file");
        return 84;
    }
    if (handle_error(st, file, binary, &utils) == 84)
        return 84;
    utils.ptr = handle_mmap(file, binary, utils, st.st_size);
    if (!utils.ptr)
        return 84;
    if (((Elf64_Ehdr *)utils.ptr)->e_ident[EI_CLASS] == ELFCLASS64)
        utils.elf_64 = true;
    ret = handle_nm(file, binary, utils);
    close(utils.fd);
    if (munmap(utils.ptr, st.st_size) == -1)
        return 84;
    return ret;
}