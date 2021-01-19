/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:40:30 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/01/19 18:31:39 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
//Hay que pasar id pero también los args de num_phi, time_to_die etc.
//Sin hacer copias del struct innecesarias.
static void		*primum_vivere(void *philo_id)
{
	unsigned long		id;

	id = *(unsigned long *)(&philo_id);
//gettimeofday aquí y si no ha comido en time_to_die, end
	pthread_mutex_lock(&g_mutex_forks);
printf("Hola Mundo, soy el Filósofo %lu\n", id);
	if ((id != 0)
		&& (g_forks[id - 1] == 1) && (g_forks[id] == 1))
	{
		g_forks[id] = 0;
		g_forks[id - 1] = 0;
printf("\tÑam Ñam\n");
	//Deinde Filosofare
	}
	else if ((id == 0)
		&& (g_forks[g_args.num_phi - 1] == 1) && (g_forks[0] == 1))
	{
		g_forks[g_args.num_phi - 1] = 0;
		g_forks[0] = 0;
printf("\tÑam Ñam\n");
	//Deinde filosofare
	}
	else
printf("\t¡Que me quedo sin comer!\n");
	pthread_mutex_unlock(&g_mutex_forks);
	return (NULL);
}

static int		set_and_check_args(int argc, char **argv, t_thread_data *args)
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
	pthread_t		*phi_threads;

	g_forks = NULL;
	if (((argc != 5) && (argc != 6))
		|| (set_and_check_args(argc, argv, &g_args))
		|| !(g_forks = malloc(sizeof(char) * g_args.num_phi))
		|| !(memset(g_forks, 1,  sizeof(char) * g_args.num_phi))
		|| !(phi_threads = malloc(sizeof(pthread_t) * g_args.num_phi))
		|| !(phi_id = malloc(sizeof(unsigned long) * g_args.num_phi)))
		return (1);
	pthread_mutex_init(&g_mutex_forks, NULL);
	i = 0;
	while (i++ < g_args.num_phi)
	{
		phi_id[i] = i;
		if ((pthread_create(&phi_threads[i], NULL, primum_vivere,
			(void *) phi_id[i])) || (pthread_join(phi_threads[i], NULL)))
			return (1);
	}
	i = 0;
	while (i++ < g_args.num_phi)
		printf("fork #%lu: %d\n", i, g_forks[i]);
	garbage_collection(&phi_threads, &phi_id);
	return (0);
}
