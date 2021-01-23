/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:34:28 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/01/23 21:43:23 by aleon-ca         ###   ########.fr       */
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

typedef struct				s_params
{
	unsigned long			num_phi;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	unsigned long			num_must_eat;
	int						deadflag;
}							t_program_args;

t_program_args				g_args;
char						*g_forks;
pthread_t					*g_phi_threads;
pthread_mutex_t				g_mutex_forks;
pthread_mutex_t				g_mutex_stdout;
pthread_mutex_t				g_mutex_start;

int							ft_strlen(char *str);
unsigned long				ft_atoul(char *str);
char						*ft_ultoa(unsigned long n);
char						*ft_ltoa(long n);

long						get_timestamp(struct timeval *t, struct timeval *u);

void						*primum_vivere(void *philo_id);

#endif
