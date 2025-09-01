NAME    := philo
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -fsanitize=address -g
THREADS := -lpthread

SRC     := 	src/philo.c \
			src/philo_manage.c\
			src/philo_utils.c\
           
OBJ     := $(SRC:src/%.c=obj/%.o)
DEP     := $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(THREADS) $^ -o $@

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re