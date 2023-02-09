# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/09 13:54:38 by alyasar           #+#    #+#              #
#    Updated: 2023/02/09 14:00:45 by alyasar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++98

INC =	vector.hpp \
		vector_iterator.hpp \
		map.hpp \
		rb_tree.hpp \
		rb_tree_iterator.hpp \
		stack.hpp \
		pair.hpp \
		utility.hpp

SRC =	main.cpp

OBJ =	$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all