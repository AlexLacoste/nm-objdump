/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** help
*/

#include <stdio.h>

int print_help(char *binary)
{
    printf("Usage: %s <file(s)>\n", binary);
    return 0;
}