##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## compile the lib and basic rules
##

CC	= epiclang

CFLAGS = -Iinclude

EPICLANGFLAGS = -Wall -Wextra -I include/

MEMORYLEAKSFLAGS = -fsanitize=address

LDFLAGS = -L.

LDLIBS  = -lcrypt

ARG = -o $(NAME)

SRC	= src/main.c \
	src/auth.c \
	src/arg.c \
	src/get.c \

OBJ 	= $(SRC:.c=.o)

NAME	= my_sudo

all:	compile

compile: $(OBJ)
	@$(CC) $(LDFLAGS) $(OBJ) $(ARG) $(LDLIBS)

debug: $(OBJ)
	@$(CC) $(LDFLAGS) $(EPICLANGFLAGS) $(MEMORYLEAKSFLAGS) $(OBJ) $(ARG) $(LDLIBS) -g

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

.PHONY: fclean all
re: fclean all
