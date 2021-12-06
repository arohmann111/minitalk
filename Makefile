# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/15 11:40:50 by arohmann          #+#    #+#              #
#    Updated: 2021/10/19 15:18:02 by arohmann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

FLAGS = -Wall -Werror -Wextra -Ilibft -Llibft -lft

LPATH = ./libft/

SRC_S = server.c

SRC_C = client.c

SRC_S_B = server_bonus.c

SRC_C_B = client_bonus.c

.PHONY: libft all clean fclean re bonus $(NAME)

all: $(NAME)

$(NAME): libft
	gcc $(FLAGS) $(SRC_S) -o server
	gcc $(FLAGS) $(SRC_C) -o client

libft:
	@make -C $(LPATH)

clean:
	rm -f client
	rm -f server
	make clean -C $(LPATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LPATH)

re: fclean all

bonus: libft
	gcc $(FLAGS) $(SRC_S_B) -o server
	gcc $(FLAGS) $(SRC_C_B) -o client