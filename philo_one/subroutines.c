/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:13:18 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/03 16:48:43 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	new_usleep(struct timeval *time, unsigned long time_lapse)
{
	unsigned long	time_objective;
	unsigned long	current_time;

	gettimeofday(time + 2, NULL);
	current_time = get_timestamp(time, time + 2);
	time_objective = current_time + time_lapse;
	while (current_time < time_objective)
	{
		usleep(100);
		gettimeofday(time + 2, NULL);
		current_time = get_timestamp(time, time + 2);
	}
}

static int	capto_furca(unsigned long id, struct timeval *time)
{
	unsigned long	left;

	left = (id != 0) ? id - 1 : g_args.num_phi - 1;
	pthread_mutex_lock(&g_mutex_waiter);
	if ((g_forks[id] == 1) && (g_forks[left] == 1))
	{
		g_forks[id] = 0;
		gettimeofday(time + 2, NULL);
		printchange(get_timestamp(time, time + 2), id, FORK_STR);
		g_forks[left] = 0;
		gettimeofday(time + 2, NULL);
		printchange(get_timestamp(time, time + 2), id, FORK_STR);
		pthread_mutex_unlock(&g_mutex_waiter);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&g_mutex_waiter);
		return (0);
	}
}

static void	philosophare(unsigned long id, struct timeval *time, int *meals)
{
	unsigned long	left;

	left = (id != 0) ? id - 1 : g_args.num_phi - 1;
	gettimeofday(time + 1, NULL);
	printchange(get_timestamp(time, time + 1), id, EAT_STR);
	new_usleep(time, g_args.time_to_eat);
	(*meals)++;
	if ((g_args.num_must_eat) && (*meals == g_args.num_must_eat))
	{
		pthread_mutex_lock(&g_mutex_meals);
		g_args.num_satiated++;
		pthread_mutex_unlock(&g_mutex_meals);
	}
	pthread_mutex_lock(&g_mutex_waiter);
	g_forks[id] = 1;
	g_forks[left] = 1;
	pthread_mutex_unlock(&g_mutex_waiter);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, SLEEP_STR);
	new_usleep(time, g_args.time_to_sleep);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, THINK_STR);
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
	int					meals_had;

	id = *(unsigned long *)(&philo_id);
	meals_had = 0;
	gettimeofday(time, NULL);
	gettimeofday(time + 1, NULL);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, THINK_STR);
	while (!(g_args.deadflag) && (g_args.num_satiated != g_args.num_phi))
	{
		if (capto_furca(id, time))
			philosophare(id, time, &meals_had);
		tunc_moriatur(id, time);
	}
	return (NULL);
}
