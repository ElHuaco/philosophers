/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:13:18 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/01/30 12:11:22 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	capto_furca(unsigned long id, struct timeval *t, int *frk_hld)
{
	//Probar arbiter/waiter también, sin que hablen entre ellos.
	pthread_mutex_lock(&g_mutex_forks);
	if (!(id % 2))
	{
		if ((frk_hld[0] == 0) && (((id != 0) && (g_forks[id - 1] == 1))
			|| ((id == 0) && (g_forks[g_args.num_phi - 1] == 1))))
		{
			(id != 0) ? (g_forks[id - 1] = 0)
				: (g_forks[g_args.num_phi - 1] = 0);
			frk_hld[0] = 1;
			gettimeofday(t + 2, NULL);
			printchange(get_timestamp(t, t + 2), id, FORK_STR);
		}
		if ((frk_hld[1] == 0) && (g_forks[id] == 1))
		{
			g_forks[id] = 0;
			frk_hld[1] = 1;
			gettimeofday(t + 2, NULL);
			printchange(get_timestamp(t, t + 2), id, FORK_STR);
		}
	}
	else
	{
		if ((frk_hld[1] == 0) && (g_forks[id] == 1))
		{
			g_forks[id] = 0;
			frk_hld[1] = 1;
			gettimeofday(t + 2, NULL);
			printchange(get_timestamp(t, t + 2), id, FORK_STR);
		}
		if ((frk_hld[0] == 0) && (((id != 0) && (g_forks[id - 1] == 1))
			|| ((id == 0) && (g_forks[g_args.num_phi - 1] == 1))))
		{
			(id != 0) ? (g_forks[id - 1] = 0)
				: (g_forks[g_args.num_phi - 1] = 0);
			frk_hld[0] = 1;
			gettimeofday(t + 2, NULL);
			printchange(get_timestamp(t, t + 2), id, FORK_STR);
		}
	}
	pthread_mutex_unlock(&g_mutex_forks);
}

static void	philosophare(unsigned long i, struct timeval *t, int *f, int *m)
{
	gettimeofday(t + 1, NULL);
	printchange(get_timestamp(t, t + 1), i, EAT_STR);
	usleep(g_args.time_to_eat * 1000);
	(*m)++;
	if ((g_args.num_must_eat) && (*m == g_args.num_must_eat))
	{
		pthread_mutex_lock(&g_mutex_start);
		g_args.num_satiated++;
		pthread_mutex_unlock(&g_mutex_start);
	}
	pthread_mutex_lock(&g_mutex_forks);
	g_forks[i] = 1;
	(i != 0) ? (g_forks[i - 1] = 1) : (g_forks[g_args.num_phi - 1] = 1);
	pthread_mutex_unlock(&g_mutex_forks);
//	gettimeofday(t + 2, NULL);
//	printchange(get_timestamp(t, t + 2), i, "dropped both forks\n");
	f[0] = 0;
	f[1] = 0;
	gettimeofday(t + 2, NULL);
	printchange(get_timestamp(t, t + 2), i, SLEEP_STR);
	usleep(g_args.time_to_sleep * 1000);
	gettimeofday(t + 2, NULL);
	printchange(get_timestamp(t, t + 2), i, THINK_STR);
}

static void	tunc_moriatur(unsigned long id, struct timeval *time)
{
	gettimeofday(time + 2, NULL);
	if (get_timestamp(time + 1, time + 2) >= g_args.time_to_die)
	{
		printchange(get_timestamp(time, time + 2), id, DEATH_STR);
		g_args.deadflag = 1;
	}
}

void		*primum_vivere(void *philo_id)
{
	unsigned long		id;
	struct timeval		time[3];
	int					forks_held[2];
	int					meals_had;

	id = *(unsigned long *)(&philo_id);
	forks_held[0] = 0;
	forks_held[1] = 0;
	meals_had = 0;
	pthread_mutex_lock(&g_mutex_start);
	gettimeofday(time, NULL);
	gettimeofday(time + 1, NULL);
	pthread_mutex_unlock(&g_mutex_start);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, THINK_STR);
	while (!(g_args.deadflag) && (g_args.num_satiated != g_args.num_phi))
	{
		capto_furca(id, time, forks_held);
		if ((forks_held[0]) && (forks_held[1]))
			philosophare(id, time, forks_held, &meals_had);
		tunc_moriatur(id, time);
	}
	return (NULL);
}
