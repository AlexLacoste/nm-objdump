##
## EPITECH PROJECT, 2021
## B-PSU-400-BDX-4-1-nmobjdump-alexandre.lacoste
## File description:
## Makefile
##


CFLAGS			=	-I./include -Wall -Wextra

NAME_NM			=	my_nm

NAME_OBJDUMP	=	my_objdump

FILES_NM		=	main.c

SRC_NM			= 	$(addprefix nm/, $(FILES_NM))

FILES_OBJDUMP	=	main.c					\
					handle_header.c			\
					handle_sections.c		\
					help.c					\
					my_objdump.c

SRC_OBJDUMP		= 	$(addprefix objdump/, $(FILES_OBJDUMP))

OBJ_NM			=	$(SRC_NM:.c=.o)

OBJ_OBJDUMP		=	$(SRC_OBJDUMP:.c=.o)

all:	$(NAME_NM) $(NAME_OBJDUMP)

$(NAME_NM):	$(OBJ_NM)
	gcc -o $(NAME_NM) $(OBJ_NM)

$(NAME_OBJDUMP):	$(OBJ_OBJDUMP)
	gcc -o $(NAME_OBJDUMP) $(OBJ_OBJDUMP)

nm:	$(NAME_NM)

objdump:	$(NAME_OBJDUMP)

# tests_run:
# 	@rm -rf *.gc*
# 	gcc -o unit_test $(TESTS) -I./include --coverage -lcriterion
# 	./unit_test

clean:
	rm -f $(OBJ_NM) $(OBJ_OBJDUMP)

fclean:	clean
	rm -f $(NAME_NM) $(NAME_OBJDUMP)
	# rm -f tests/*.o
	# rm -f unit_test
	# rm -f *.gc*

re:	fclean all

.PHONY: all $(NAME_NM) $(NAME_OBJDUMP) clean fclean re