/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.lacoste
** File description:
** main
*/

#include <string.h>
#include "../include/objdump.h"

int main(int ac, char **av)
{
    int ret = 0;

    if (ac == 1)
        return my_objdump("a.out", av[0]);
    if (ac == 2 && (strcmp(av[1], "-h") == 0 || strcmp(av[1], "--help") == 0))
        return print_help(av[0]);
    for (int i = 1; i < ac; i++)
        ret += my_objdump(av[i], av[0]);
    return (ret > 0) ? 84 : 0;
}