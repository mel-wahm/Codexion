CC = cc
CFLAGS = -pthread
NAME = codexion

SRC = utils.c parser.c validator.c initialize_data.c main.c cleanup.c simulation.c dongles.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

it:	all clean

.PHONY: all clean fclean re
