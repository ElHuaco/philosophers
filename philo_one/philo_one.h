/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:34:28 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/03 19:41:02 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
#include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define FORK_STR "has taken a fork\n"
# define EAT_STR "is eating\n"
# define SLEEP_STR "is sleeping\n"
# define THINK_STR "is thinking\n"
# define DEATH_STR "died\n"

typedef struct		s_params
{
	unsigned long	num_phi;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	num_must_eat;
	int				deadflag;
	unsigned long	num_satiated;
}					t_program_args;

typedef struct		s_queue
{
	void			*content;
	struct s_queue	*next;
}					t_list;

t_program_args		g_args;
t_list				g_queue;
char				*g_forks;
pthread_mutex_t		g_mutex_waiter;
pthread_mutex_t		g_mutex_stdout;
pthread_mutex_t		g_mutex_meals;

int					ft_strlen(char *str);
unsigned long		ft_atoul(char *str);
char				*ft_ultoa(unsigned long n);
void				printchange(unsigned long t, unsigned long i, char *s);

t_list				*ft_lstnew(void *content);
t_list				*ft_last(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdel_back(t_list *alst);
void				ft_lstclear(t_list **alst);

unsigned long		get_timestamp(struct timeval *t, struct timeval *u);

void				*primum_vivere(void *philo_id);

#endif
