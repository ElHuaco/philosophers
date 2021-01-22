/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:40:30 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/01/22 11:00:08 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int		set_and_check_args(int argc, char **argv, t_program_args *args)
{
	args->num_phi = ft_atoul(argv[1]);
	args->time_to_die = ft_atold(argv[2]);
	args->time_to_eat = ft_atold(argv[3]);
	args->time_to_sleep = ft_atold(argv[4]);
	if (argc == 6)
	{
		args->num_must_eat = ft_atoul(argv[5]);
		return (!(args->num_phi) || !(args->time_to_die)
			|| !(args->time_to_eat) || !(args->time_to_sleep)
			|| !(args->num_must_eat));
	}
	else
	{
		args->num_must_eat = 0;
		return (!(args->num_phi) || !(args->time_to_die)
			|| !(args->time_to_eat) || !(args->time_to_sleep));
	}
}

static int		create_threads(pthread_t *g_phi_threads, unsigned long *phi_id)
{
	unsigned long		i;

	if (pthread_mutex_lock(&g_mutex_start))
		return (1);
	i = 0;
	while (i < g_args.num_phi)
	{
		phi_id[i] = i;
		if ((pthread_create(&g_phi_threads[i], NULL, primum_vivere,
			(void *) phi_id[i])))
			return (1);
		++i;
	}
	if (pthread_mutex_unlock(&g_mutex_start))
		return (1);
	return (0);
}

static void		garbage_collection(unsigned long **id)
{
	pthread_mutex_destroy(&g_mutex_forks);
	pthread_mutex_destroy(&g_mutex_stdout);
	pthread_mutex_destroy(&g_mutex_start);
	free(g_forks);
	free(g_phi_threads);
	free(*id);
}

int				main(int argc, char **argv)
{
	unsigned long	i;
	unsigned long	*phi_id;

	if (((argc != 5) && (argc != 6))
		|| (set_and_check_args(argc, argv, &g_args))
		|| !(g_forks = malloc(sizeof(char) * g_args.num_phi))
		|| !(memset(g_forks, 1,  sizeof(char) * g_args.num_phi))
		|| !(g_phi_threads = malloc(sizeof(pthread_t) * g_args.num_phi))
		|| !(phi_id = malloc(sizeof(unsigned long) * g_args.num_phi))
		|| (pthread_mutex_init(&g_mutex_forks, NULL))
		|| (create_threads(g_phi_threads, phi_id)))
		return (1);
	i = 0;
	while (i < g_args.num_phi)
		pthread_join(g_phi_threads[i++], NULL);
	i = 0;
	while (i < g_args.num_phi)
	{
		printf("\tfork #%lu: %d\n", i, g_forks[i]);
		++i;
	}
	garbage_collection(&phi_id);
	return (0);
}
