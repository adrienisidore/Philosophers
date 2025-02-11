# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 11:40:55 by aisidore          #+#    #+#              #
#    Updated: 2025/02/11 12:19:26 by aisidore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c \
	  utils.c \
	  error.c

OBJ = $(SRC:.c=.o)

FL = -Wall -Wextra -Werror -pthread

all: philo

philo: ${OBJ}
	cc ${FL} -o philo ${OBJ}

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f philo

re: fclean all
rebonus: fclean bonus

.PHONY: all clean fclean re