NAME = Philo
CC = cc
FLAGS = -Wall -Wextra -Werror
SRC =	parse.c \
		philo_manage.c \
		routine.c \
		utils.c	\
		main.c \

OBJ = $(SRC:.c=.o)
HEADER = philo.h

all: $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJ)
		$(CC) $(FLAGS) -o $(NAME) $(OBJ)
	
%.o: %.c $(HEADER)
		$(CC) $(FLAGS) -I$(LIBFT_DIR) -I. -c $< -o $@

clean:
		rm -f $(OBJ)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
