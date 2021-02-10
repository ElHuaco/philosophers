/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 09:05:08 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/10 09:07:53 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

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
sem_t				*g_sem_forks;
sem_t				*g_sem_stdio;
sem_t				*g_sem_meals;
sem_t				*g_sem_time;

/*
**	utils.c
*/
int					ft_strlen(char *str);
unsigned long		ft_atoul(char *str);
char				*ft_ultoa(unsigned long n);
void				printchange(unsigned long tme, unsigned long id, char *str);
/*
**	main.c
*/
unsigned long		get_timestamp(struct timeval *time1, struct timeval *time2);
void				init_timestamps(struct timeval **time_add, t_monitor *data);
/*
**	subroutines.c
*/
void				*primum_vivere(void *philo_id);

#endif
