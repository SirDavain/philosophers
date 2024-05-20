NAME = philo

SRC_DIR = ./src
OBJ_DIR = ./obj

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/init.c $(SRC_DIR)/check.c
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g

all: $(NAME)

NAME: $(SRC_DIR)/%.c philosophers.h
	@cc $(CFLAGS) -o 

#$(NAME): $(OBJ)
#	$(CC) $^ -o $(NAME)

#%.o: $(SRC_DIR)/%.c philosophers.h
#	@make -p $(OBJ_DIR)
#	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: NAME all clean fclean re