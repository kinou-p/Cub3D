# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apommier <apommier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/13 16:27:49 by apommier          #+#    #+#              #
#    Updated: 2022/06/15 18:39:09 by apommier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= Cub3D
SRCS	= srcs/main.c\
			srcs/cast_ray/get_texture_array.c\
			srcs/cast_ray/cast_ray.c\
			srcs/cast_ray/utils.c\
			srcs/parsing/parse_map.c\
			srcs/parsing/check_color_texture.c
			
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