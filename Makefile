# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apommier <apommier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/13 16:27:49 by apommier          #+#    #+#              #
#    Updated: 2022/06/11 13:31:36 by apommier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= Cub3D
SRCS	= srcs/main.c\
			srcs/get_texture_array.c\
			srcs/cast_ray.c\
			srcs/parsing/parse_map.c\
			srcs/parsing/check_color_texture.c\
			srcs/utils.c
OBJS	= ${SRCS:.c=.o}
CC		= gcc
LIB		= -L ./mlx -lmlx -lXext -lX11 -lm
CFLAGS	= -Wall -Wextra -g
RM		= rm -rf
LIBFT	= ./libft

${NAME}: ${OBJS} 
		@make bonus -C ${LIBFT} 
		@${CC} ${CFLAGS} ${OBJS} ${LIBFT}/libft.a ${LIB} -o ${NAME}
	
all:	${NAME} bonus

clean:
		@${RM} ${OBJS}
		@make clean -C ${LIBFT}

fclean:	clean
		@${RM} ${NAME}
		@make fclean -C ${LIBFT}
		
re: 	fclean all

.PHONY: all clean fclean re bonus 