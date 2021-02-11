/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:40:30 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/11 12:20:16 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int		set_and_check_args(int argc, char **argv)
{
	g_args.num_phi = ft_atoul(argv[1]);
	if (g_args.num_phi == 1)
		return (1);
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

	if (!(g_sem_forks = sem_open("forks", O_CREAT, 0664, g_args.num_phi))
		|| !(g_sem_stdio = sem_open("stdio", O_CREAT, 0664, 1))
		|| !(g_sem_meals = sem_open("meals", O_CREAT, 0664, 1))
		|| !(g_sem_time = sem_open("time", O_CREAT, 0664, 1)))
		return (1);
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

int				main(int argc, char **argv)
{
	unsigned long	*phi_id;
	pthread_t		*phi_threads;

	sem_unlink("forks");
	sem_unlink("stdio");
	sem_unlink("meals");
	sem_unlink("time");
	if (((argc != 5) && (argc != 6))
		|| (set_and_check_args(argc, argv))
		|| !(phi_id = malloc(sizeof(unsigned long) * g_args.num_phi))
		|| !(phi_threads = malloc(sizeof(pthread_t) * g_args.num_phi))
		|| (create_threads(phi_threads, phi_id)))
		return (1);
	free(phi_threads);
	free(phi_id);
	sem_close(g_sem_forks);
	sem_close(g_sem_stdio);
	sem_close(g_sem_meals);
	sem_close(g_sem_time);
	sem_unlink("forks");
	sem_unlink("stdio");
	sem_unlink("meals");
	sem_unlink("time");
	return (0);
}
