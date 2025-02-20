# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 11:40:55 by aisidore          #+#    #+#              #
#    Updated: 2025/02/20 18:25:51 by aisidore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Si je modifie le Makefile alors "make" ne crame pas qu'il a change
OBJ_DIR = objets

SRC = main.c \
	  utils.c \
	  parsing.c

OBJ = $(OBJ_DIR)/main.o \
	  $(OBJ_DIR)/utils.o \
	  $(OBJ_DIR)/parsing.o

# FL = -Wall -Wextra -Werror -pthread -fsanitize=thread
FL = -Wall -Wextra -Werror

all: philo

philo: ${OBJ}
	cc ${FL} -o philo ${OBJ}

${OBJ_DIR}/%.o: %.c
	@mkdir -p ${OBJ_DIR}
	cc -c ${FL} $< -o $@

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f philo

re: fclean all

.PHONY: all clean fclean re