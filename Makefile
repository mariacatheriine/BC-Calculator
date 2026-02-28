NAME := my_bc.exe
CC := gcc
CFLAGS := -Wall -Wextra -Werror -Iinclude

SRC := src/main.c src/error.c src/dynarray.c src/lexer.c src/shunting.c src/eval.c
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

# address sanitizer
asan: CFLAGS += -g3 -fsanitize=address 
asan: re

.PHONY: all clean fclean re asan