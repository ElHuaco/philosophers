/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:40:30 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/01/18 18:22:00 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		main(int argc, void **argv)
{
	int		i;
	void	*status;

	if (((argc != 5) && ((argc != 6) || (argv[5] < 0))) || (argv[1] <= 0)
		|| (argv[2] < 0) || (argv[3] < 0) || (argv[4] < 0))
		return (1);
	if (!(g_forks = malloc(argv[1])) || !(memset(g_forks, 1,  argv[1]))
		|| !(g_threads = malloc(sizeof(pthread_t) * argv[1])))
		return (1);
	pthread_mutex_init(&g_mutex_forks, NULL);
	i = -1;
	while (++i < argv[1])
		pthread_create(&g_threads[i], NULL, primum_vivere, (void *)i);
	i = -1;
	while (++i < argv[1])
		pthread_join(&g_threads[i], &status);
	return (0);
}
