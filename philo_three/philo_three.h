/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:07:04 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/09 12:43:01 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <semaphore.h>

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
}					t_program_args;

typedef struct		s_shared
{
	sem_t			*sem_dead;
	sem_t			*sem_forks;
	sem_t			*sem_stdio;
	sem_t			**sem_meals;
	int				*pid;
}					t_shared;

typedef struct		s_monitor
{
	unsigned long	id;
	struct timeval	*time_zero;
	struct timeval	*time_eat;
	t_shared		*data;
}					t_monitor;

t_program_args		g_args;
/*
**	utils.c
*/
int					ft_strlen(char *str);
unsigned long		ft_atoul(char *str);
char				*ft_ultoa(unsigned long n);
void				pch(unsigned long t, unsigned long i, char *s, t_shared *d);
/*
**	timestamps.c
*/
unsigned long		get_timestamp(struct timeval *time1, struct timeval *time2);
void				init_timestamps(struct timeval **time_add, t_monitor *data);
/*
**	subroutines.c
*/
void				primum_vivere(unsigned long id, t_shared *data);
/*
**	meal_monitor.c
*/
void				are_satiated(t_shared *data);
#endif
