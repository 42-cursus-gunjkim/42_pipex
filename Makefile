NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = pipe.c process_utils.c error_utils.c cmd_utils.c pipex_split.c here_doc.c
BONUS_SRCS = pipe_bonus.c process_utils_bonus.c error_utils_bonus.c cmd_utils_bonus.c pipex_split_bonus.c here_doc_bonus.c
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: make_mandatory
bonus: make_bonus

make_mandatory: $(OBJS)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./libft -lft
	touch $@

make_bonus: $(BONUS_OBJS)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJS) -L./libft -lft
	touch $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	rm -f make_mandatory make_bonus
	$(MAKE) -C ./libft fclean

fclean: clean
	rm -f $(NAME)

re: 
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus
