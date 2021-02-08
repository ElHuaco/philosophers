/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:40:30 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/08 12:44:02 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int		set_and_check_args(int argc, char **argv)
{
	g_args.num_phi = ft_atoul(argv[1]);
	g_args.time_to_die = ft_atoul(argv[2]);
	g_args.time_to_eat = ft_atoul(argv[3]);
	g_args.time_to_sleep = ft_atoul(argv[4]);
	g_args.num_satiated = 0;
	if (argc == 6)
	{
		g_args.num_must_eat = ft_atoul(argv[5]);
		return (!(g_args.num_phi) || !(g_args.time_to_die)
			|| !(g_args.time_to_eat) || !(g_args.time_to_sleep)
			|| !(g_args.num_must_eat));
	}
	else
	{
		g_args.num_must_eat = 0;
		return (!(g_args.num_phi) || !(g_args.time_to_die)
			|| !(g_args.time_to_eat) || !(g_args.time_to_sleep));
	}
}

static int		create_threads(pthread_t *phi_threads, unsigned long *phi_id)
{
	unsigned long	i;

	i = 0;
	while (i < g_args.num_phi)
	{
		phi_id[i] = i;
		if ((pthread_create(&phi_threads[i], NULL, primum_vivere,
			(void *)phi_id[i])))
			return (1);
		++i;
	}
	i = 0;
	while (i < g_args.num_phi)
		pthread_join(phi_threads[i++], NULL);
	return (0);
}

unsigned long	get_timestamp(struct timeval *t1, struct timeval *t2)
{
	return ((unsigned long)((t2->tv_sec - t1->tv_sec) * 1000)
		+ (unsigned long)((t2->tv_usec - t1->tv_usec) / 1000));
}

void			init_timestamps(struct timeval *time, t_monitor *data)
{
	gettimeofday(time, NULL);
	data->time_zero = time;
	gettimeofday(time + 1, NULL);
	data->time_eat = time + 1;
	gettimeofday(time + 2, NULL);
}

int				main(int argc, char **argv)
{
	unsigned long	*phi_id;
	pthread_t		*phi_threads;
	sem_t			*sem_forks;
	sem_t			*sem_stdio;
	sem_t			*sem_meals;

	if (((argc != 5) && (argc != 6))
		|| (set_and_check_args(argc, argv))
		|| !(phi_threads = malloc(sizeof(pthread_t) * g_args.num_phi))
		|| !(phi_id = malloc(sizeof(unsigned long) * g_args.num_phi))
		|| !(sem_forks = sem_open("forks", O_CREAT, 0664, g_args.num_phi))
		|| !(sem_stdio = sem_open("stdio", O_CREAT, 0664, 1))
		|| !(sem_meals = sem_open("meals", O_CREAT, 0664, 1))
		|| (create_threads(phi_threads, phi_id)))
		return (1);
	free(phi_threads);
	free(phi_id);
	sem_close(sem_forks);
	sem_close(sem_stdio);
	sem_close(sem_meals);
	sem_unlink("forks");
	sem_unlink("stdio");
	sem_unlink("meals");
	return (0);
}