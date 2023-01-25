NAME 	= philo
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror
SRC_DIR = src/
SOURCE 	= $(wildcard $(SRC_DIR)*.c)
OBJS	= $(SOURCE: .c=.o)

all:$(NAME)

$(NAME) : $(OBJS)
	$(CC) -I ./ $(CFLAGS) $(OBJS) -o $(NAME)

re: fclean all

push:
	bash git.sh "Day 08"

fclean: 
	@rm -f $(NAME)