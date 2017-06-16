# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alam <alam@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/10 14:29:56 by alam              #+#    #+#              #
#    Updated: 2017/04/28 15:53:25 by alam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

FILES = fractol.c image.c draw.c hooks.c key.c mouse.c init.c color.c\
		fractal_julia.c fractal_mandelbrot.c fractal_newton.c ui.c

INCLUDES = -I libft -I minilibx

LIBRARY = -L libft -lft -L minilibx -lmlx

FRAMEWORK = -framework OpenGL -framework AppKit

OBJECTS = $(FILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

all: libft minilibx $(NAME)

$(NAME): $(OBJECTS)
	gcc $(CFLAGS) $(INCLUDES) $(LIBRARY) $(FRAMEWORK) -o $(NAME) $(OBJECTS)

libft:
	make -C libft/ all

minilibx:
	make -C minilibx/

%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $^

clean:
	rm -f $(OBJECTS)

fclean: clean
	make -C libft/ fclean
	make -C minilibx/ clean
	rm -f $(NAME)

re: fclean all

new: clean all

.PHONY: all clean fclean re libft minilibx
