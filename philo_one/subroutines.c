/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:13:18 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/11 11:33:21 by aleon-ca         ###   ########.fr       */
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
		usleep(10);
		gettimeofday(time + 2, NULL);
		current_time = get_timestamp(time, time + 2);
	}
}

static int	is_allowed_eat(unsigned long id, unsigned long left)
{
	return ((g_forks[id] == 1) && (g_forks[left] == 1)
		&& ((g_queue == g_args.num_phi) || (g_queue == id)
			|| ((g_queue > id)
			&& (g_queue - id != 1) && (g_queue - id != g_args.num_phi - 1))
			|| ((g_queue < id)
			&& (id - g_queue != 1) && (id - g_queue != g_args.num_phi - 1))));
}

static int	capto_furca(unsigned long id, struct timeval *time, int *meals)
{
	unsigned long	left;

	left = (id != 0) ? id - 1 : g_args.num_phi - 1;
	gettimeofday(time + 2, NULL);
	pthread_mutex_lock(&g_mutex_waiter);
	if (is_allowed_eat(id, left))
	{
		if (g_queue == id)
			g_queue = g_args.num_phi;
		g_forks[id] = 0;
		printchange(get_timestamp(time, time + 2), id, FORK_STR);
		g_forks[left] = 0;
		printchange(get_timestamp(time, time + 2), id, FORK_STR);
		pthread_mutex_unlock(&g_mutex_waiter);
		return (1);
	}
	else if ((((g_forks[id]) && !g_forks[left])
		|| ((!g_forks[id]) && (g_forks[left]))) && (g_queue == g_args.num_phi)
		&& get_timestamp(time + 1, time + 2) > g_args.time_to_eat
		+ (*meals > 0) * g_args.time_to_sleep)
		g_queue = id;
	pthread_mutex_unlock(&g_mutex_waiter);
	return (0);
}

static void	philosophare(unsigned long id, struct timeval *time, int *meals)
{
	unsigned long	left;

	left = (id != 0) ? id - 1 : g_args.num_phi - 1;
	gettimeofday(time + 1, NULL);
	printchange(get_timestamp(time, time + 1), id, EAT_STR);
	new_usleep(time, g_args.time_to_eat);
	pthread_mutex_lock(&g_mutex_waiter);
	g_forks[id] = 1;
	g_forks[left] = 1;
	pthread_mutex_unlock(&g_mutex_waiter);
	(*meals)++;
	if ((g_args.num_must_eat) && (*meals == g_args.num_must_eat))
	{
		pthread_mutex_lock(&g_mutex_meals);
		g_args.num_satiated++;
		pthread_mutex_unlock(&g_mutex_meals);
	}
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, SLEEP_STR);
	new_usleep(time, g_args.time_to_sleep);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, THINK_STR);
}

void		*primum_vivere(void *philo_id)
{
	unsigned long		id;
	struct timeval		time[3];
	int					meals_had;
	unsigned long		time_lapse;

	id = *(unsigned long *)(&philo_id);
	meals_had = 0;
	gettimeofday(time, NULL);
	gettimeofday(time + 1, NULL);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, THINK_STR);
	while (!(g_args.deadflag) && (g_args.num_satiated != g_args.num_phi))
	{
		if (capto_furca(id, time, &meals_had))
			philosophare(id, time, &meals_had);
		gettimeofday(time + 2, NULL);
		if ((time_lapse = get_timestamp(time + 1, time + 2))
			>= g_args.time_to_die)
		{
			printchange(time_lapse, id, DEATH_STR);
			g_args.deadflag = 1;
		}
	}
	return (NULL);
}
