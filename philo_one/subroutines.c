/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:13:18 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/01/23 21:54:17 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	print_status_change(long time, unsigned long id, char *str)
{
	char		*time_str;
	char		*id_str;

	time_str = ft_ltoa(time);
	id_str = ft_ultoa(id + 1);
	pthread_mutex_lock(&g_mutex_stdout);
	write(1, time_str, ft_strlen(time_str));
	write(1, " ", 1);
	write(1, id_str, ft_strlen(id_str));
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&g_mutex_stdout);
	free(id_str);
	free(time_str);
}

static void	capto_furca(unsigned long id, struct timeval *time, int *forks_held)
{
	pthread_mutex_lock(&g_mutex_forks);
	if (((id != 0) && (g_forks[id - 1] == 1)) || ((id == 0)
		&& (g_forks[g_args.num_phi - 1] == 1)))
	{
		(id != 0) ? (g_forks[id - 1] = 0)
			: (g_forks[g_args.num_phi - 1] = 0);
		(*forks_held)++;
		gettimeofday(time + 2, NULL);
		print_status_change(get_timestamp(time, time + 2), id, FORK_STR);
	}
	pthread_mutex_unlock(&g_mutex_forks);
	pthread_mutex_lock(&g_mutex_forks);
	if (g_forks[id] == 1)
	{
		g_forks[id] = 0;
		(*forks_held)++;
		gettimeofday(time + 2, NULL);
		print_status_change(get_timestamp(time, time + 2), id, FORK_STR);
	}
	pthread_mutex_unlock(&g_mutex_forks);
}

static void	philosophare(unsigned long id, struct timeval *t, int *frk, int *ml)
{
	gettimeofday(t + 1, NULL);
	print_status_change(get_timestamp(t, t + 1), id, EAT_STR);
	usleep(g_args.time_to_eat * 1000.0);
	(*ml)++;
	pthread_mutex_lock(&g_mutex_forks);
	g_forks[id] = 1;
	(id != 0) ? (g_forks[id - 1] = 1)
		: (g_forks[g_args.num_phi - 1] = 1);
	pthread_mutex_unlock(&g_mutex_forks);
	*frk = 0;
	gettimeofday(t + 2, NULL);
	print_status_change(get_timestamp(t, t + 2), id, SLEEP_STR);
	usleep(g_args.time_to_sleep * 1000.0);
	gettimeofday(t + 2, NULL);
	print_status_change(get_timestamp(t, t + 2), id, THINK_STR);
}

static void	tunc_moriatur(unsigned long id, struct timeval *time)
{
	long	time_since_last_meal;

	gettimeofday(time + 2, NULL);
	time_since_last_meal = get_timestamp(time + 1, time + 2);
	if (time_since_last_meal >= g_args.time_to_die)
	{
		g_args.deadflag = 1;
		print_status_change(time_since_last_meal, id, DEATH_STR);
	}
}

void		*primum_vivere(void *philo_id)
{
	unsigned long		id;
	struct timeval		time[3];//time[0] inicio; time[1] comida; time[2] evento
	int					forks_held;
	int					meals_had;

	id = *(unsigned long *)(&philo_id);
	forks_held = 0;
	meals_had = 0;
	pthread_mutex_lock(&g_mutex_start);
	gettimeofday(time, NULL);
	pthread_mutex_unlock(&g_mutex_start);
	gettimeofday(time + 2, NULL);
	print_status_change(get_timestamp(time, time + 2), id, THINK_STR);
	while (!(g_args.deadflag))
	{
		if ((g_args.num_must_eat) && (meals_had == g_args.num_must_eat))
			pthread_detach(g_phi_threads[id]);
		capto_furca(id, time, &forks_held);
		if (forks_held == 2)
			philosophare(id, time, &forks_held, &meals_had);
		else
			tunc_moriatur(id, time);
	}
	return (NULL);
}
