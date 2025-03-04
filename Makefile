# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 11:40:55 by aisidore          #+#    #+#              #
#    Updated: 2025/03/04 19:41:37 by aisidore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Si je modifie le Makefile alors "make" ne crame pas qu'il a change
OBJ_DIR = objets

SRC = ft_inidt.c \
	  main.c \
	  ft_parser.c \
	  setget.c \
	  sim.c \
	  utils.c

OBJ = $(OBJ_DIR)/ft_inidt.o \
	  $(OBJ_DIR)/main.o \
	  $(OBJ_DIR)/ft_parser.o \
	  $(OBJ_DIR)/setget.o \
	  $(OBJ_DIR)/sim.o \
	  $(OBJ_DIR)/utils.o
	  

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