/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** nm
*/

#ifndef NM_H_
#define NM_H_

#include "shared.h"

int my_nm(char *file, char *binary, int ac);
int print_help(char *binary);

int handle_nm(char *file, char *binary, utils_t utils, int ac);
char set_symbol(int st_type, int st_bind, size_t st_value);

#endif /* !NM_H_ */
