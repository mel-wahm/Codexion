CC = cc
CFLAGS = -pthread -g
NAME = codexion

SRC = utils.c parser.c validator.c initialize_data.c\
	  main.c cleanup.c simulation.c simulation_utils.c dongles.c dongle_utils.c monitor.c heap_queue.c heap_utils.c

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
