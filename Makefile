CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
NAME = codexion

SRC = utils.c parser.c data.c main.c coders.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

makeit:	all clean

.PHONY: all clean fclean re
