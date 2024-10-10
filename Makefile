NAME	= philo
CC		= cc
RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror -g

SRC =	src/main.c \
		src/situation.c \
		src/utils.c \
		src/utils1.c \
		src/init.c \
		src/free.c \

OBJ_DIR = .objs

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re
