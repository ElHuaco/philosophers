/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:13:18 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/01/22 12:30:17 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	print_status_change(struct timeval *t, unsigned long id, char *str)
{
	float	time;
	char	*time_str;
	char	*id_str;

	gettimeofday(t + 1, NULL);
	t[1].tv_sec -= t[0].tv_sec;
	t[1].tv_usec -= t[0].tv_usec;
	time = t[1].tv_sec * 1000.0 + t[1].tv_usec / 1000.0;
	time_str = ft_ldtoa(time);
	id_str = ft_ultoa(id + 1);
	pthread_mutex_lock(&g_mutex_stdout);
	write(1, time_str, ft_strlen(time_str));
	write(1, " ", 1);
	write(1, id_str, ft_strlen(id_str));
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&g_mutex_stdout);
	free(time_str);
	free(id_str);
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
		print_status_change(time, id, FORK_STR);
	}
	pthread_mutex_unlock(&g_mutex_forks);
	pthread_mutex_lock(&g_mutex_forks);
	if (g_forks[id] == 1)
	{
		g_forks[id] = 0;
		(*forks_held)++;
		print_status_change(time, id, FORK_STR);
	}
	pthread_mutex_unlock(&g_mutex_forks);
}

static void	philosophare(unsigned long i, struct timeval *t, int *f, int *m)
{
	print_status_change(t, i, EAT_STR);
	usleep(g_args.time_to_eat * 1000.0);
	(*m)++;
	pthread_mutex_lock(&g_mutex_forks);
	g_forks[i] = 1;
	(i != 0) ? (g_forks[i - 1] = 1)
		: (g_forks[g_args.num_phi - 1] = 1);
	pthread_mutex_unlock(&g_mutex_forks);
	*f = 0;
	print_status_change(t, i, SLEEP_STR);
	usleep(g_args.time_to_sleep * 1000.0);
	print_status_change(t, i, THINK_STR);
}

static void	tunc_moriatur(unsigned long id, struct timeval *time)
{
	float	time_since_last_meal;
	char	*time_str;
	char	*id_str;

	gettimeofday(time + 1, NULL);
	time[1].tv_sec -= time[0].tv_sec;
	time[1].tv_usec -= time[0].tv_usec;
	time_since_last_meal = time[1].tv_sec * 1000.0 + time[1].tv_usec / 1000.0;
	if (time_since_last_meal >= g_args.time_to_die)
	{
		g_args.deadflag = 1;
		time_str = ft_ldtoa(time_since_last_meal);
		id_str = ft_ultoa(id + 1);
		pthread_mutex_lock(&g_mutex_stdout);
		write(1, time_str, ft_strlen(time_str));
		write(1, " ", 1);
		write(1, id_str, ft_strlen(id_str));
		write(1, " ", 1);
		write(1, DEATH_STR, ft_strlen(DEATH_STR));
		pthread_mutex_unlock(&g_mutex_stdout);
		free(time_str);
		free(id_str);
	}
}

void		*primum_vivere(void *philo_id)
{
	unsigned long		id;
	struct timeval		time[2];
	int					forks_held;
	int					meals_had;

	id = *(unsigned long *)(&philo_id);
	forks_held = 0;
	meals_had = 0;
	pthread_mutex_lock(&g_mutex_start);
	gettimeofday(time, NULL);
	pthread_mutex_unlock(&g_mutex_start);
	print_status_change(time, id, THINK_STR);
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

