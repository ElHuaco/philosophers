/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:34:28 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/09 12:58:19 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

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

t_program_args		g_args;
unsigned long		g_queue;
char				*g_forks;
pthread_mutex_t		g_mutex_waiter;
pthread_mutex_t		g_mutex_stdout;
pthread_mutex_t		g_mutex_meals;
/*
**	utils.c
*/
int					ft_strlen(char *str);
unsigned long		ft_atoul(char *str);
char				*ft_ultoa(unsigned long n);
void				printchange(unsigned long t, unsigned long i, char *s);
/*
**	main.c
*/
unsigned long		get_timestamp(struct timeval *t, struct timeval *u);
/*
**	subroutines.c
*/
void				*primum_vivere(void *philo_id);

#endif
