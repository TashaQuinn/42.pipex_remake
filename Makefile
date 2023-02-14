NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRC = pipex.c libft.c

HEADER = pipex.h

OBJ = $(SRC:.c=.o)

%.o: %.c	${HEADER} 
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ 

all: $(NAME)

clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re

val:
	valgrind --show-leak-kinds=all -s ./$(NAME)