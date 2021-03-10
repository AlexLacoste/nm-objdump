/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** nm
*/

#ifndef NM_H_
#define NM_H_

#include "shared.h"

int my_nm(char *file, char *binary);
int print_help(char *binary);

int handle_nm(char *file, char *binary, utils_t utils);

#endif /* !NM_H_ */
