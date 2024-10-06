NAME = philo

CC = cc
CFLAGS = -g -pthread #-Wall -Wextra -Werror

OBJ_DIR	= obj

SRC = main.c utils.c init.c check.c routine.c
OBJ	= $(SRC:%.c=$(OBJ_DIR)/%.o)

HEADERS	= -I.

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(HEADERS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
