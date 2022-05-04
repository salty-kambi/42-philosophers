# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 10:06:54 by lsuau             #+#    #+#              #
#    Updated: 2022/02/15 18:13:58 by lsuau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAMEX = philo

INC = philo.h

SRC = main.c parsing.c stock.c philo_init.c data.c philo_thread.c

GCC = gcc -Wall -Werror -Wextra #-fsanitize=address

OBJ_DIR = obj/
OBJ = ${addprefix ${OBJ_DIR}, ${SRC:.c=.o}}

all : ${NAMEX}

${OBJ_DIR}%.o : %.c ${INC} Makefile
	${GCC} -c $< -o $@

${NAMEX}: ${OBJ} ${INC}
	${GCC} ${OBJ} -o ${NAMEX}

${OBJ}: | ${OBJ_DIR}

${OBJ_DIR}:
	mkdir ${OBJ_DIR}

clean :
	rm -rf ${OBJ_DIR}

fclean : clean
	rm -f ${NAMEX}

re : fclean all

.PHONY: all clean fclean re
