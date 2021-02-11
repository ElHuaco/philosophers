/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:13:18 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/11 12:26:14 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	capto_furca(unsigned long id, struct timeval *time)
{
	sem_wait(g_sem_forks);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, FORK_STR);
	sem_wait(g_sem_forks);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, FORK_STR);
}

static void	philosophare(unsigned long id, struct timeval *time, int *meals)
{
	sem_wait(g_sem_time);
	gettimeofday(time + 1, NULL);
	sem_post(g_sem_time);
	printchange(get_timestamp(time, time + 1), id, EAT_STR);
	new_usleep(time, g_args.time_to_eat);
	(*meals)++;
	if ((g_args.num_must_eat) && (*meals == g_args.num_must_eat))
	{
		sem_wait(g_sem_meals);
		g_args.num_satiated++;
		sem_post(g_sem_meals);
	}
	sem_post(g_sem_forks);
	sem_post(g_sem_forks);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, SLEEP_STR);
	new_usleep(time, g_args.time_to_sleep);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, THINK_STR);
}

static void	post_all(void)
{
	unsigned long i;

	sem_post(g_sem_time);
	i = 0;
	while (i < g_args.num_phi)
	{
		sem_post(g_sem_forks);
		sem_post(g_sem_forks);
	}
}

static void	*tunc_moriatur(void *data)
{
	unsigned long	id;
	struct timeval	current_time;
	t_monitor		*monitor_data;

	monitor_data = (t_monitor *)data;
	id = monitor_data->id;
	while (!(g_args.deadflag) && (g_args.num_satiated != g_args.num_phi))
	{
		gettimeofday(&current_time, NULL);
		sem_wait(g_sem_time);
		if (get_timestamp(monitor_data->time_eat, &current_time)
			> g_args.time_to_die)
		{
			printchange(get_timestamp(monitor_data->time_zero, &current_time),
				id, DEATH_STR);
			g_args.deadflag = 1;
			post_all();
			return (NULL);
		}
		sem_post(g_sem_time);
	}
	return (NULL);
}

void		*primum_vivere(void *philo_id)
{
	unsigned long		id;
	struct timeval		*time;
	int					meals_had;
	pthread_t			the_reaper;
	t_monitor			data;

	id = *(unsigned long *)(&philo_id);
	data.id = id;
	meals_had = 0;
	time = malloc(sizeof(struct timeval) * 3);
	init_timestamps(&time, &data);
	pthread_create(&the_reaper, NULL, tunc_moriatur, (void *)&data);
	pthread_detach(the_reaper);
	printchange(get_timestamp(time, time + 2), id, THINK_STR);
	while (!(g_args.deadflag) && (g_args.num_satiated != g_args.num_phi))
	{
		capto_furca(id, time);
		philosophare(id, time, &meals_had);
	}
	free(time);
	pthread_detach(the_reaper);
	return (NULL);
}
