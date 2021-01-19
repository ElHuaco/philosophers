/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:40:30 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/01/19 17:47:46 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		*primum_vivere(void *philo_id)
{
	usleep(10);
	pthread_mutex_lock(&g_mutex_forks);
printf("Hola Mundo, soy el Filósofo %lu\n", *(unsigned long *)(&philo_id));
	g_forks[*(unsigned long *)(&philo_id)] = 0;
	pthread_mutex_unlock(&g_mutex_forks);
	return (NULL);
}

static int		set_and_check_args(int argc, char **argv, t_args *args)
{
	args->num_phi = ft_atoul(argv[1]);
	args->time_to_die = ft_atould(argv[2]);
	args->time_to_eat = ft_atould(argv[3]);
	args->time_to_sleep = ft_atould(argv[4]);
	if (argc == 6)
	{
		args->num_must_eat = ft_atoul(argv[5]);
		return (!(args->num_phi) || !(args->time_to_die)
			|| !(args->time_to_eat) || !(args->time_to_sleep)
			|| !(args->num_must_eat));
	}
	else
		return (!(args->num_phi) || !(args->time_to_die)
			|| !(args->time_to_eat) || !(args->time_to_sleep));
}

static void		garbage_collection(pthread_t **philos, unsigned long **id)
{
	pthread_mutex_destroy(&g_mutex_forks);
	free(g_forks);
	free(*philos);
	free(*id);
}

int				main(int argc, char **argv)
{
	unsigned long	i;
	unsigned long	*phi_id;
	t_args			args;
	pthread_t		*phi_threads;

	g_forks = NULL;
	if (((argc != 5) && (argc != 6)) || (set_and_check_args(argc, argv, &args))
		|| !(g_forks = malloc(sizeof(char) * args.num_phi))
		|| !(memset(g_forks, 1,  sizeof(char) * args.num_phi))
		|| !(phi_threads = malloc(sizeof(pthread_t) * args.num_phi))
		|| !(phi_id = malloc(sizeof(unsigned long) * args.num_phi)))
		return (1);
	pthread_mutex_init(&g_mutex_forks, NULL);
	i = -1;
	while (++i < args.num_phi)
	{
		phi_id[i] = i;
		if ((pthread_create(&phi_threads[i], NULL, primum_vivere,
			(void *) phi_id[i])) || (pthread_join(phi_threads[i], NULL)))
			return (1);
	}
	i = -1;
	while (++i < args.num_phi)
		printf("fork #%lu: %d\n", i, g_forks[i]);
	garbage_collection(&phi_threads, &phi_id);
	return (0);
}
