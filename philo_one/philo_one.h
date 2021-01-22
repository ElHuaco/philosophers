/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:34:28 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/01/22 10:59:49 by aleon-ca         ###   ########.fr       */
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
	long double				time_to_die;
	long double				time_to_eat;
	long double				time_to_sleep;
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
char						*ft_strchr(char *str, int c);
unsigned long				ft_atoul(char *str);
long double					ft_atold(char *str);

char						*ft_ultoa(unsigned long n);
char						*ft_ldtoa(long double n);

void						*primum_vivere(void *philo_id);

#endif
