# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plisieck <plisieck@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/20 14:08:06 by plisieck          #+#    #+#              #
#    Updated: 2015/03/16 14:36:42 by plisieck         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_minishell1
SRC = main.c sh1_1.c sh1_2.c sh1_3.c sh1_4.c sh1_5.c sh1_6.c sh1_7.c sh1_8.c
OBJ = main.o sh1_1.o sh1_2.o sh1_3.o sh1_4.o sh1_5.o sh1_6.o sh1_7.o sh1_8.o
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@gcc -c $(FLAGS) $(SRC)
	@make -C libft/
	@gcc -o $(NAME) $(FLAGS) $(OBJ) libft/libft.a
	@echo "\033[33;32mDone !"


clean:
	@make clean -C libft
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
