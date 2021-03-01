/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.lacoste
** File description:
** my_objdump
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

#include "../include/objdump.h"

static int handle_open(char *file, char *binary, utils_t *utils)
{
    // TODO: gestion d'erreur -> permission denied etc
    (void)binary;
    utils->fd = open(file, O_RDONLY);
    if (utils->fd == -1) {
        fprintf(stderr, "%s: '%s' %s\n", binary, file, "No such file");
        return 84;
    }
    return 0;
}

static void *handle_mmap(char *file, utils_t utils)
{
    void *tmp = NULL;

    (void)file; //
    int size = lseek(utils.fd, 0, SEEK_END);
    if (size == -1)
        return NULL;
    tmp = mmap(NULL, size, PROT_READ, MAP_SHARED, utils.fd, 0);
    if (!tmp) {
        // TODO: handle error not ordinary file
    }
    return tmp;
}

int my_objdump(char *file, char *binary)
{
    utils_t utils = {.fd = 0, .size = 0};
    void *tmp = NULL;
    int ret = 0;

    if (handle_open(file, binary, &utils) == 84)
        return 84;
    tmp = handle_mmap(file, utils);
    if (!tmp) {
        close(utils.fd);
        return 84;
    }
    if (((Elf64_Ehdr *)tmp)->e_ident[EI_CLASS] == ELFCLASS64)
        ret = handle_64(file, binary, tmp, utils);
    else {
        // handle 32
    }
    close(utils.fd);
    return ret;
}