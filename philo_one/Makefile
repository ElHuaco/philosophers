# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 17:33:29 by aleon-ca          #+#    #+#              #
#    Updated: 2021/01/25 08:48:05 by aleon-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c subroutines.c utils.c

OBJS = $(SRCS:.c=.o)

NAME = philo_one

#INCLUDE = -I. -lpthread
FLAGS = -Werror -Wextra -Wall
GCC = gcc $(FLAGS)

RM = rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
	$(GCC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
