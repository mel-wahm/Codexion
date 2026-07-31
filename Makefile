CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g -ISrc
NAME = codexion

SRC = Src/utils.c \
      Src/parser.c \
      Src/validator.c \
      Src/initialize_data.c \
      Src/main.c \
      Src/cleanup.c \
      Src/simulation.c \
      Src/simulation_utils.c \
      Src/dongles.c \
      Src/dongle_utils.c \
      Src/monitor.c \
      Src/heap_queue.c \
      Src/heap_utils.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

it: all clean

.PHONY: all clean fclean re
