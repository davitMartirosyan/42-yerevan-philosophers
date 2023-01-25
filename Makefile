NAME 	= philo
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror
SRC_DIR = src/
SOURCE 	= $(wildcard $(SRC_DIR)*.c)
OBJS	= $(patsubst %.c, %.o, $(SOURCE))

all:$(NAME)

$(NAME) : $(OBJS) ./header.h
	$(CC)  $(CFLAGS) -pthread $(OBJS) -o $(NAME)

%.o : %.c header.h
	$(CC) -I ./ $(CFLAGS) -c $< -o $@

re: fclean all

push:
	bash git.sh $(ARG)

clean:
	rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)