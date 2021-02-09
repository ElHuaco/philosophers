/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:18:56 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/09 12:53:45 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

static void	capto_furca(unsigned long id, struct timeval *time, t_shared *data)
{
	sem_wait(data->sem_forks);
	gettimeofday(time + 2, NULL);
	pch(get_timestamp(time, time + 2), id, FORK_STR, data);
	sem_wait(data->sem_forks);
	gettimeofday(time + 2, NULL);
	pch(get_timestamp(time, time + 2), id, FORK_STR, data);
}

static void	f(unsigned long id, struct timeval *time, int *meals, t_shared *dat)
{
	gettimeofday(time + 1, NULL);
	pch(get_timestamp(time, time + 1), id, EAT_STR, dat);
	new_usleep(time, g_args.time_to_eat);
	(*meals)++;
	if ((g_args.num_must_eat) && (*meals == g_args.num_must_eat))
		sem_post(dat->sem_meals[id]);
	sem_post(dat->sem_forks);
	sem_post(dat->sem_forks);
	gettimeofday(time + 2, NULL);
	pch(get_timestamp(time, time + 2), id, SLEEP_STR, dat);
	new_usleep(time, g_args.time_to_sleep);
	gettimeofday(time + 2, NULL);
	pch(get_timestamp(time, time + 2), id, THINK_STR, dat);
}

static void	*tunc_moriatur(void *monitor_data)
{
	unsigned long	id;
	struct timeval	current_time;
	t_monitor		*casted_mon;

	casted_mon = (t_monitor *)monitor_data;
	id = casted_mon->id;
	while (1)
	{
		usleep(10);
		gettimeofday(&current_time, NULL);
		if (get_timestamp(casted_mon->time_eat, &current_time)
			> g_args.time_to_die)
		{
			pch(get_timestamp(casted_mon->time_zero, &current_time),
				id, DEATH_STR, casted_mon->data);
			sem_post(casted_mon->data->sem_dead);
			return (NULL);
		}
	}
}

void		primum_vivere(unsigned long id, t_shared *data)
{
	struct timeval		*time;
	int					meals_had;
	pthread_t			the_reaper;
	t_monitor			monitor_data;

	monitor_data.id = id;
	monitor_data.data = data;
	meals_had = 0;
	time = malloc(sizeof(struct timeval) * 3);
	init_timestamps(&time, &monitor_data);
	pthread_create(&the_reaper, NULL, tunc_moriatur, (void *)&monitor_data);
	pthread_detach(the_reaper);
	pch(get_timestamp(time, time + 2), id, THINK_STR, data);
	while (1)
	{
		capto_furca(id, time, data);
		f(id, time, &meals_had, data);
	}
}
