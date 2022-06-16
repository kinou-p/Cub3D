# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apommier <apommier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/13 16:27:49 by apommier          #+#    #+#              #
#    Updated: 2022/06/16 16:38:38 by apommier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
SRCS	= srcs/main.c\
			srcs/cast_ray/get_texture_array.c\
			srcs/cast_ray/cast_ray.c\
			srcs/cast_ray/find_wall.c\
			srcs/cast_ray/utils.c\
			srcs/cast_ray/set_back.c\
			srcs/cast_ray/ray_casting.c\
			srcs/key_event/key.c\
			srcs/utils/cub_utils.c\
			srcs/utils/quit_game.c\
			srcs/parsing/parse_map.c\
			srcs/parsing/is_a_file.c\
			srcs/parsing/check_map.c\
			srcs/parsing/check_map_utils.c\
			srcs/parsing/utils_parsing.c\
			srcs/parsing/check_color_texture.c
			
OBJS	= ${SRCS:.c=.o}
CC		= gcc
LIB		= -L ./mlx -lmlx -lXext -lX11 -lm
CFLAGS	= -Wall -Wextra -Werror -g
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