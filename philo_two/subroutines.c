/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:13:18 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/09 09:00:57 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

static void	capto_furca(unsigned long id, struct timeval *time)
{
	sem_t	*sem_fork;

	sem_fork = sem_open("forks", 0);
	sem_wait(sem_fork);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, FORK_STR);
	sem_wait(sem_fork);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, FORK_STR);
	sem_close(sem_fork);
}

static void	philosophare(unsigned long id, struct timeval *time, int *meals)
{
	sem_t	*sem_fork;
	sem_t	*sem_meals;

	sem_fork = sem_open("forks", 0);
	sem_meals = sem_open("meals", 0);
	gettimeofday(time + 1, NULL);
	printchange(get_timestamp(time, time + 1), id, EAT_STR);
	new_usleep(time, g_args.time_to_eat);
	(*meals)++;
	if ((g_args.num_must_eat) && (*meals == g_args.num_must_eat))
	{
		sem_wait(sem_meals);
		g_args.num_satiated++;
		sem_post(sem_meals);
	}
	sem_post(sem_fork);
	sem_post(sem_fork);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, SLEEP_STR);
	new_usleep(time, g_args.time_to_sleep);
	gettimeofday(time + 2, NULL);
	printchange(get_timestamp(time, time + 2), id, THINK_STR);
	sem_close(sem_fork);
	sem_close(sem_meals);
}

static void	*tunc_moriatur(void *data)
{
	unsigned long	id;
	struct timeval	*time_origin;
	struct timeval	*time_last_meal;
	struct timeval	current_time;
	unsigned long	time_lapse;

	id = ((t_monitor *)data)->id;
	time_origin = ((t_monitor *)data)->time_zero;
	while (!(g_args.deadflag) && (g_args.num_satiated != g_args.num_phi))
	{
		usleep(5);
		gettimeofday(&current_time, NULL);
		time_last_meal = ((t_monitor *)data)->time_eat;
		if ((time_lapse = get_timestamp(time_last_meal, &current_time))
			> g_args.time_to_die)
		{
//printchange(get_timestamp(time_last_meal, &current_time), id, "LAST_MEAL\n");
			printchange(get_timestamp(time_origin, &current_time),
				id, DEATH_STR);
			g_args.deadflag = 1;
		}
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
	printchange(get_timestamp(time, time + 2), id, THINK_STR);
	while (!(g_args.deadflag) && (g_args.num_satiated != g_args.num_phi))
	{
		capto_furca(id, time);
		philosophare(id, time, &meals_had);
	}
	pthread_detach(the_reaper);
	free(time);
	return (NULL);
}
