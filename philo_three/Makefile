# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 17:33:29 by aleon-ca          #+#    #+#              #
#    Updated: 2021/02/09 12:22:10 by aleon-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c subroutines.c utils.c timestamps.c meal_monitor.c

OBJS = $(SRCS:.c=.o)

NAME = philo_three

INCLUDE = -I. -lpthread
#RACE_BUGS = -g -fsanitize=thread
FLAGS = -Werror -Wextra -Wall $(INCLUDE) #$(RACE_BUGS)
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
