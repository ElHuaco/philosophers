/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:13:18 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/01/25 13:10:03 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	capto_furca(unsigned long id, struct timeval *t, int *frks_hld)
{
	pthread_mutex_lock(&g_mutex_forks);
	if (((id != 0) && (g_forks[id - 1] == 1)) || ((id == 0)
		&& (g_forks[g_args.num_phi - 1] == 1)))
	{
		(id != 0) ? (g_forks[id - 1] = 0)
			: (g_forks[g_args.num_phi - 1] = 0);
		(*frks_hld)++;
		gettimeofday(t + 2, NULL);
		printchange(get_timestamp(t, t + 2), id, FORK_STR);
	}
	pthread_mutex_unlock(&g_mutex_forks);
	pthread_mutex_lock(&g_mutex_forks);
	if (g_forks[id] == 1)
	{
		g_forks[id] = 0;
		(*frks_hld)++;
		gettimeofday(t + 2, NULL);
		printchange(get_timestamp(t, t + 2), id, FORK_STR);
	}
	pthread_mutex_unlock(&g_mutex_forks);
}

static void	philosophare(unsigned long i, struct timeval *t, int *f, int *m)
{
	gettimeofday(t + 1, NULL);
	printchange(get_timestamp(t, t + 1), i, EAT_STR);
	usleep(g_args.time_to_eat * 1000);
	gettimeofday(t + 1, NULL);
	(*m)++;
	pthread_mutex_lock(&g_mutex_forks);
	g_forks[i] = 1;
	(i != 0) ? (g_forks[i - 1] = 1)
		: (g_forks[g_args.num_phi - 1] = 1);
	pthread_mutex_unlock(&g_mutex_forks);
	*f = 0;
	gettimeofday(t + 2, NULL);
	printchange(get_timestamp(t, t + 2), i, SLEEP_STR);
	usleep(g_args.time_to_sleep * 1000);
	gettimeofday(t + 2, NULL);
	printchange(get_timestamp(t, t + 2), i, THINK_STR);
}

static void	tunc_moriatur(unsigned long id, struct timeval *time)
{
	unsigned long	time_since_last_meal;

	gettimeofday(time + 2, NULL);
	time_since_last_meal = get_timestamp(time + 1, time + 2);
	if (time_since_last_meal >= g_args.time_to_die)
	{
		g_args.deadflag = 1;
		printchange(get_timestamp(time, time + 2), id, DEATH_STR);
	}
}

void		plenus_sum(void)
{
	pthread_mutex_lock(&g_mutex_start);
	g_args.num_satiated++;
	pthread_mutex_unlock(&g_mutex_start);
}

void		*primum_vivere(void *philo_id)
{
	unsigned long		id;
	struct timeval		time[3];
	int					forks_held;
	int					meals_had;

	id = *(unsigned long *)(&philo_id);
	forks_held = 0;
	meals_had = 0;
	pthread_mutex_lock(&g_mutex_start);
	gettimeofday(time, NULL);
	gettimeofday(time + 1, NULL);
	pthread_mutex_unlock(&g_mutex_start);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, THINK_STR);
	while (!(g_args.deadflag) && (g_args.num_satiated != g_args.num_phi))
	{
		capto_furca(id, time, &forks_held);
		if (forks_held == 2)
			philosophare(id, time, &forks_held, &meals_had);
		else
			tunc_moriatur(id, time);
		if ((g_args.num_must_eat) && (meals_had == g_args.num_must_eat))
			plenus_sum();
	}
	return (NULL);
}
