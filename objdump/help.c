/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.lacoste
** File description:
** help
*/

#include <stdio.h>
#include "../include/objdump.h"

int print_help(char *binary)
{
    printf("Usage: %s <file(s)>\n", binary);
    return 0;
}