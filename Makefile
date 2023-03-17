NAME = pipex
CC = @cc
RM = rm -f
CFLAGS = -Werror -Wextra -Wall
# -fsanitize=thread -g3
SRC = pipex.c utils.c ft_printf/ft_printf.c ft_printf/ft_putchar.c ft_printf/ft_putnbr.c ft_printf/ft_putnbr_add.c \
ft_printf/ft_putnbr_u_dec.c ft_printf/ft_putstr.c ft_printf/ft_strlen.c libft/ft_split.c libft/ft_strchr.c \
libft/ft_strjoin.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):$(OBJ)
	@make -C costumizing/
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	@make -C costumizing mse7
	@$(RM) $(OBJ)
	@echo "\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME)
	@$(RM) $(B_NAME)

re: fclean all
