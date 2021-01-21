/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:34:28 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/01/21 13:41:17 by aleon-ca         ###   ########.fr       */
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
pthread_mutex_t				g_mutex_forks;
pthread_mutex_t				g_mutex_stdout;
pthread_mutex_t				g_mutex_deadflag;

int							ft_strlen(char *str);
char						*ft_strchr(char *str, int c);
unsigned long				ft_atoul(char *str);
long double					ft_atould(char *str);

void						*primum_vivere(void *philo_id);

#endif
