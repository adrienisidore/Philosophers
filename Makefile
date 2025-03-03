# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 11:40:55 by aisidore          #+#    #+#              #
#    Updated: 2025/03/03 17:18:40 by aisidore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Si je modifie le Makefile alors "make" ne crame pas qu'il a change
OBJ_DIR = objets

SRC = ft_inidt.c \
	  main.c \
	  parsing.c \
	  setget.c \
	  simulation.c \
	  utils.c

OBJ = $(OBJ_DIR)/ft_inidt.o \
	  $(OBJ_DIR)/main.o \
	  $(OBJ_DIR)/parsing.o \
	  $(OBJ_DIR)/setget.o \
	  $(OBJ_DIR)/simulation.o \
	  $(OBJ_DIR)/utils.o \
	  

FL = -Wall -Wextra -Werror -pthread -fsanitize=thread
# FL = -Wall -Wextra -Werror -pthread

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