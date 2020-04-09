# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elindber <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 19:39:02 by elindber          #+#    #+#              #
#    Updated: 2019/12/20 11:54:57 by elindber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = ./srcs/create_list.c	./srcs/main.c ./srcs/validate_file.c \
	  ./srcs/create_map.c ./srcs/place_tmns.c

LIB = ./libft/libft.a

all: $(NAME)

$(NAME):
	@ make -C libft/ fclean && make -C libft/
	@ gcc -Wall -Werror -Wextra -o $(NAME) $(SRC) $(LIB)
	@ echo source files compiled and executable created
	@ echo READY TO RUN

clean:
	@ /bin/rm -f *.o
	@ make -C libft/ clean
	@ echo dummy clean done

fclean: clean
	@ /bin/rm -f $(NAME)
	@ make -C libft/ fclean
	@ echo executable removed

re: fclean all
