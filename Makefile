# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ijaaskel <ijaaskel@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/22 12:42:19 by ijaaskel          #+#    #+#              #
#    Updated: 2023/01/22 12:42:22 by ijaaskel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fractol

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror

SRC_DIR		=	src/
INC_DIR		=	includes/
OBJ_DIR		=	objs/
LIBFT		=	libft/libft.a

ifneq (,$(wildcard /usr/local/include/mlx.h))
MLX			=	-I /usr/local/include
else
MLX			=	-I /usr/X11/include
endif

ifneq (,$(wildcard /usr/local/lib/libmlx.a))
MLX			+=	-L /usr/local/lib -lmlx
else ifneq (,$(wildcard /usr/local/lib/libmlx.dylib))
MLX			+=	-L /usr/local/lib -lmlx
else
MLX			+=	-L /usr/X11/lib -lmlx
endif

UNAME		:=	$(shell uname -s)
ifeq ($(UNAME), Darwin)
FRAMEWORKS	=	-framework OpenGL -framework AppKit
endif
ifeq ($(UNAME), Linux)
MLX			+=	-lX11 -lXext
endif

MATH		=	-lm

HDR			=	fractol.h

SRCS		=	main.c			\
				error.c			\
				draw_images.c	\
				hooks.c			\
				zoom.c			\
				fractol.c		\
				julia.c			\
				mandelbrot.c	\
				koch.c			\
				draw_line.c

OBJS		=	main.o			\
				error.o			\
				draw_images.o	\
				hooks.o			\
				zoom.o			\
				fractol.o		\
				julia.o			\
				mandelbrot.o	\
				koch.o			\
				draw_line.o

all:			$(NAME)

$(NAME):		$(OBJS)
	@$(CC) $(FLAGS) $(OBJS) $(MLX) $(LIBFT) $(MATH) $(FRAMEWORKS) -o $@

%.o:	$(SRC_DIR)%.c	$(INC_DIR)fractol.h	$(LIBFT)
	@$(CC) -c $(FLAGS) -I $(INC_DIR) $< -o $@

$(LIBFT):
	@make -C libft/

clean:
	@make clean -C libft
	@rm -v -f $(OBJS)

fclean:			clean
	@make fclean -C libft
	@rm -v -f $(NAME)

re:				fclean all

rec:			re
	@make clean

.PHONY: all clean flcean re rec
