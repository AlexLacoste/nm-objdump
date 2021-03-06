/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.lacoste
** File description:
** my_objdump
*/

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "../include/objdump.h"

static int handle_open(char *file, utils_t *utils)
{
    utils->fd = open(file, O_RDONLY);
    if (utils->fd == -1)
        return 84;
    // TODO: check si c'est bien un elf ou un ar rc sinon return 84 avec file format
    return 0;
}

static void *handle_mmap(char *file, char *binary, utils_t utils, size_t size)
{
    void *tmp = NULL;

    tmp = mmap(NULL, size, PROT_READ, MAP_SHARED, utils.fd, 0);
    if (!tmp) {
        close(utils.fd);
        return NULL;
    }
    if (((Elf64_Ehdr *)tmp)->e_shnum * ((Elf64_Ehdr *)tmp)->e_shentsize
                + ((Elf64_Ehdr *)tmp)->e_shoff
            != size
        && ((Elf32_Ehdr *)tmp)->e_shnum * ((Elf32_Ehdr *)tmp)->e_shentsize
                + ((Elf32_Ehdr *)tmp)->e_shoff
            != size) {
        fprintf(stderr, "%s: %s: %s\n", binary, file, "file truncated");
        close(utils.fd);
        return NULL;
    }
    return tmp;
}

static int handle_error(
    struct stat st, char *file, char *binary, utils_t *utils)
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

int my_objdump(char *file, char *binary)
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
    ret = handle_objdump(file, binary, utils);
    close(utils.fd);
    if (munmap(utils.ptr, st.st_size) == -1)
        return 84;
    return ret;
}