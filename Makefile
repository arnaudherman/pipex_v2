# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aherman <aherman@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 12:15:54 by aherman           #+#    #+#              #
#    Updated: 2023/09/19 22:10:51 by aherman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS := src/pipex.c\
		src/pipex_utils.c\
		src/pipex_childs.c\
		src/pipex_need.c\
		src/pipex_split.c\

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
