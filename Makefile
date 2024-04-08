# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luguilla <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 14:13:02 by luguilla          #+#    #+#              #
#    Updated: 2022/03/10 10:59:04 by luguilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	$(wildcard *.c)

OBJS	=	${SRCS:.c=.o}

NAME	=	pipex

CC	=		gcc

CFLAGS	=	-Wall -Wextra -Werror -g


RM	=		rm -f

.c.o:	pipex
		$(CC) $(CFLAGS) -I. -c $< -o $@

$(NAME): $(OBJS) $(MLX)
	$(CC) -o $(NAME) $(OBJS) $(LFLAGS)

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
