/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:40:30 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/09 10:35:35 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int		set_and_check_args(int argc, char **argv)
{
	g_args.num_phi = ft_atoul(argv[1]);
	g_args.time_to_die = ft_atoul(argv[2]);
	g_args.time_to_eat = ft_atoul(argv[3]);
	g_args.time_to_sleep = ft_atoul(argv[4]);
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

static int		set_data(t_shared *data)
{
	sem_unlink("forks");
	sem_unlink("stdio");
	sem_unlink("meals");
	sem_unlink("dead");
	if (!(data->sem_dead = sem_open("dead", O_CREAT, 0664, 0))
		|| !(data->sem_forks = sem_open("forks", O_CREAT, 0664, g_args.num_phi))
		|| !(data->sem_stdio = sem_open("stdio", O_CREAT, 0664, 1))
		|| !(data->sem_meals = sem_open("meals", O_CREAT, 0664, 1))
		|| !(data->pid = malloc(sizeof(int) * g_args.num_phi)))
		return (1);
	else
		return (0);
}

static void		create_childs(t_shared *data)
{
	unsigned long	i;
	pid_t			pid;

	i = 0;
	while (i < g_args.num_phi)
	{
		if (!(data->pid[i] = fork()))
			primum_vivere(i, data);
		else
			++i;
	}
}

int				main(int argc, char **argv)
{
	t_shared		data;
	unsigned long	i;

	if (((argc != 5) && (argc != 6))
		|| (set_and_check_args(argc, argv))
		|| (set_data(&data)))
		return (1);
	create_childs(&data);
	sem_wait(data.sem_dead);
	i = 0;
	while (i < g_args.num_phi)
		kill(data.pid[i++], SIGKILL);
	free(data.pid);
	sem_close(data.sem_forks);
	sem_close(data.sem_stdio);
	sem_close(data.sem_meals);
	sem_close(data.sem_dead);
	sem_unlink("forks");
	sem_unlink("stdio");
	sem_unlink("meals");
	sem_unlink("dead");
	return (0);
}
