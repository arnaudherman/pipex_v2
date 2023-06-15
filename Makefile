# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aherman <aherman@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 12:15:54 by aherman           #+#    #+#              #
#    Updated: 2023/06/15 17:16:23 by aherman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS := src/pipex.c\

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
OBJS = $(SRCS:.c=.o)


all: ${NAME} ${CHECK} ${OBJS}
${NAME}: ${OBJS}
	@${MAKE} -C ./ft_printf
	@${CC} ${CFLAGS} ${OBJS} ./ft_printf/ft_printf.a -o ${NAME}

${CHECK}: ${CHECK_OBJS} 
	@${CC} ${CFLAGS} ${CHECK_OBJS} ./ft_printf/ft_printf.a -o ${CHECK}

clean: 
	@${MAKE} -C ./ft_printf fclean
	@${RM} ${OBJS}
	@${RM} ${CHECK_OBJS}

fclean: clean
	@${RM} ${NAME}
	@${RM} ${CHECK}

re: fclean all
