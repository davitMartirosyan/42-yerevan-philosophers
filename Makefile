NAME 	= philo
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror
OBJ_DIR = objs/
SOURCE 	= $(wildcard *.c)
OBJS	= $(SOURCE: .c=.o)

all:$(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS)  -pthread -c $< -o $@

fclean:
	rm -rf $(OBJ_DIR)