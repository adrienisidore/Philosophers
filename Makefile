# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 11:40:55 by aisidore          #+#    #+#              #
#    Updated: 2025/03/07 12:08:41 by aisidore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ_DIR = objets

SRC = end.c \
	  ft_inidt.c \
	  main.c \
	  ft_parser.c \
	  setget.c \
	  sim_utils.c \
	  sim.c \
	  utils.c

OBJ = $(OBJ_DIR)/end.o \
	  $(OBJ_DIR)/ft_inidt.o \
	  $(OBJ_DIR)/main.o \
	  $(OBJ_DIR)/ft_parser.o \
	  $(OBJ_DIR)/setget.o \
	  $(OBJ_DIR)/sim_utils.o \
	  $(OBJ_DIR)/sim.o \
	  $(OBJ_DIR)/utils.o

FL = -Wall -Wextra -Werror -pthread

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