NAME = parser

CC = clang

# FLAGS    = -Wall -Wextra -Werror -g

DEL = /bin/rm -f

SRCS =	./srcs/main.c\
		./gnl/get_next_line.c\
		./gnl/get_next_line_utils.c\

SRCS_O    = ${SRCS:.c=.o}

all: $(NAME)

LIBC    = ar -rcs

%.o: %.c
		${CC} ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${SRCS_O}
			make bonus -C ./libft/
		 $(CC) $(FLAGS) $(SRCS_O) -o $(NAME) -L ./libft/ -lft

fclean: clean
		$(DEL) $(NAME)
		make fclean -C ./libft/

clean:
		$(DEL) $(SRCS_O)
		make clean -C ./libft/

re: fclean all
