/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:40:30 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/01/19 13:58:03 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		*primum_vivere(void *philo_number)
{
	pthread_mutex_lock(&g_mutex_forks);
	g_forks[0] += *(unsigned long *)philo_number;
	pthread_mutex_unlock(&g_mutex_forks);
	write(1, "¡Hola mundo! Soy un filósofo.", 31);
	write(1, "\n", 1);
	return (NULL);
}

static int		set_and_check_args(int argc, char **argv, t_args *args)
{
	args->num_philosophers = ft_atoul(argv[1]);
	args->time_to_die = ft_atould(argv[2]);
	args->time_to_eat = ft_atould(argv[3]);
	args->time_to_sleep = ft_atould(argv[4]);
printf("argumentos: %lu %Lf %Lf %Lf\n", args->num_philosophers, args->time_to_die, args->time_to_eat, args->time_to_sleep);
	if (argc == 6)
	{
		args->num_must_eat = ft_atoul(argv[5]);
		return (!(args->num_philosophers) || !(args->time_to_die)
			|| !(args->time_to_eat) || !(args->time_to_sleep)
			|| !(args->num_must_eat));
	}
	else
		return (!(args->num_philosophers) || !(args->time_to_die)
			|| !(args->time_to_eat) || !(args->time_to_sleep));
}

int				main(int argc, char **argv)
{
	unsigned long	i;
	void			*status;
	t_args			args;
	pthread_t		*philo_threads;

	g_forks = NULL;
	philo_threads = NULL;
	if (((argc != 5) && (argc != 6)) || (set_and_check_args(argc, argv, &args)))
		return (1);
	if (!(g_forks = malloc(sizeof(char) * args.num_philosophers))
		|| !(memset(g_forks, 1,  sizeof(char) * args.num_philosophers))
		|| !(philo_threads = malloc(sizeof(pthread_t) * args.num_philosophers)))
		return (1);
	pthread_mutex_init(&g_mutex_forks, NULL);
printf("Creando threads...\n");
	i = -1;
	while (++i < args.num_philosophers)
		if ((pthread_create(&philo_threads[i], NULL, primum_vivere, (void *)&i)))
			return (1);
printf("Joineando threads...\n");
	i = -1;
	while (++i < args.num_philosophers)
		if ((pthread_join(philo_threads[i], &status)))
			return (1);
	i = -1;
	while (++i < args.num_philosophers)
		printf("fork #%lu: %c\n", i, g_forks[i] + '0');
	pthread_mutex_destroy(&g_mutex_forks);
	free(g_forks);
	free(philo_threads);
	return (0);
}
