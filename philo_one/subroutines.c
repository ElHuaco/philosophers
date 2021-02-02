/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:13:18 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/02 12:21:26 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	capto_furca(unsigned long id, struct timeval *time)
{
	if (id != 0)
	{
		pthread_mutex_lock(&g_mutex_forks[id - 1]);
		gettimeofday(time + 2, NULL);
		printchange(get_timestamp(time, time + 2), id, FORK_STR);
		pthread_mutex_lock(&g_mutex_forks[id]);
		gettimeofday(time + 2, NULL);
		printchange(get_timestamp(time, time + 2), id, FORK_STR);
	}
	else
	{
		pthread_mutex_lock(&g_mutex_forks[id]);
		gettimeofday(time + 2, NULL);
		printchange(get_timestamp(time, time + 2), id, FORK_STR);
		pthread_mutex_lock(&g_mutex_forks[g_args.num_phi - 1]);
		gettimeofday(time + 2, NULL);
		printchange(get_timestamp(time, time + 2), id, FORK_STR);
	}
}

static void	philosophare(unsigned long id, struct timeval *time, int *meals)
{
	gettimeofday(time + 1, NULL);
	printchange(get_timestamp(time, time + 1), id, EAT_STR);
	usleep(g_args.time_to_eat * 1000);
	(*meals)++;
	if ((g_args.num_must_eat) && (*meals == g_args.num_must_eat))
	{
		pthread_mutex_lock(&g_mutex_start);
		g_args.num_satiated++;
		pthread_mutex_unlock(&g_mutex_start);
	}
	pthread_mutex_unlock(&g_mutex_forks[(id != 0) ? (id - 1)
		: (g_args.num_phi - 1)]);
	pthread_mutex_unlock(&g_mutex_forks[id]);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, SLEEP_STR);
	usleep(g_args.time_to_sleep * 1000);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, THINK_STR);
}

static void	tunc_moriatur(unsigned long id, struct timeval *time)
{
	gettimeofday(time + 2, NULL);
	if (get_timestamp(time + 1, time + 2) > g_args.time_to_die)
	{
		printchange(get_timestamp(time, time + 2), id, DEATH_STR);
		g_args.deadflag = 1;
	}
}

void		*primum_vivere(void *philo_id)
{
	unsigned long		id;
	struct timeval		time[3];
	int					meals_had;

	id = *(unsigned long *)(&philo_id);
	meals_had = 0;
//	pthread_mutex_lock(&g_mutex_start);
	gettimeofday(time, NULL);
	gettimeofday(time + 1, NULL);
//	pthread_mutex_unlock(&g_mutex_start);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, THINK_STR);
	while (!(g_args.deadflag) && (g_args.num_satiated != g_args.num_phi))
	{
		capto_furca(id, time);
		philosophare(id, time, &meals_had);
		tunc_moriatur(id, time);
	}
	return (NULL);
}
