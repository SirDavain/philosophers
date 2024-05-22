NAME = philo

OBJ_DIR = ./obj

SRC = main.c utils.c init.c check.c routine.c
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
SRC_DIR = $(addprefix ./src/, $(SRC))
HEADER = src/philosophers.h

#CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g

all: $(NAME)

$(NAME): $(SRC_DIR) $(HEADER)
	@cc $(CFLAGS) -o $(NAME) $(SRC_DIR)

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