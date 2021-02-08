/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 09:05:08 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/08 12:22:27 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H
#include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
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
	int				deadflag;
	unsigned long	num_satiated;
}					t_program_args;

typedef struct		s_monitor
{
	unsigned long	id;
	struct timeval	*time_zero;
	struct timeval	*time_eat;
}					t_monitor;

t_program_args		g_args;

int					ft_strlen(char *str);
unsigned long		ft_atoul(char *str);
char				*ft_ultoa(unsigned long n);
void				printchange(unsigned long t, unsigned long i, char *s);

unsigned long		get_timestamp(struct timeval *t, struct timeval *u);
void				init_timestamps(struct timeval *t, t_monitor *data);

void				*primum_vivere(void *philo_id);

#endif
