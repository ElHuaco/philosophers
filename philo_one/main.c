/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:40:30 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/03 16:45:57 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

static int		create_threads(pthread_t *g_phi_threads, unsigned long *phi_id)
{
	unsigned long		i;

	i = 0;
	while (i < g_args.num_phi)
	{
		phi_id[i] = i;
		if ((pthread_create(&g_phi_threads[i], NULL, primum_vivere,
			(void *)phi_id[i])))
			return (1);
		++i;
	}
	return (0);
}

static void		garbage_collection(unsigned long **id, pthread_t **phi_threads)
{
	pthread_mutex_destroy(&g_mutex_waiter);
	pthread_mutex_destroy(&g_mutex_stdout);
	pthread_mutex_destroy(&g_mutex_meals);
	free(g_forks);
	free(*phi_threads);
	free(*id);
}

unsigned long	get_timestamp(struct timeval *t1, struct timeval *t2)
{
	return ((unsigned long)((t2->tv_sec - t1->tv_sec) * 1000)
		+ (unsigned long)((t2->tv_usec - t1->tv_usec) / 1000));
}

int				main(int argc, char **argv)
{
	unsigned long	i;
	unsigned long	*phi_id;
	pthread_t		*phi_threads;

	if (((argc != 5) && (argc != 6))
		|| (set_and_check_args(argc, argv))
		|| !(g_forks = malloc(sizeof(char) * g_args.num_phi))
		|| !(memset(g_forks, 1, sizeof(char) * g_args.num_phi))
		|| !(phi_threads = malloc(sizeof(pthread_t) * g_args.num_phi))
		|| !(phi_id = malloc(sizeof(unsigned long) * g_args.num_phi))
		|| (pthread_mutex_init(&g_mutex_meals, NULL))
		|| (pthread_mutex_init(&g_mutex_waiter, NULL))
		|| (pthread_mutex_init(&g_mutex_stdout, NULL))
		|| (create_threads(phi_threads, phi_id)))
		return (1);
	i = 0;
	while (i < g_args.num_phi)
		pthread_join(phi_threads[i++], NULL);
	garbage_collection(&phi_id, &phi_threads);
	return (0);
}
