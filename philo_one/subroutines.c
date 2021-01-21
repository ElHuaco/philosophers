/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:13:18 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/01/21 13:48:21 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		*primum_vivere(void *philo_id)
{
	unsigned long		id;
	struct timeval		time[2];
//	suseconds_t			time;

	id = *(unsigned long *)(&philo_id);
	gettimeofday(time, NULL);
//gettimeofday aquí y si no ha comido en time_to_die, end
//while (!(g_args.deadflag))
	pthread_mutex_lock(&g_mutex_forks);
	if (((id != 0) && (g_forks[id - 1] == 1) && (g_forks[id] == 1))
		|| ((id == 0) && (g_forks[g_args.num_phi - 1] == 1)
			&& (g_forks[0] == 1)))
	{
		(id != 0) ? (g_forks[id - 1] = 0) : (g_forks[g_args.num_phi - 1] = 0);
		g_forks[id] = 0;
		gettimeofday(time + 1, NULL);
		time[1].tv_sec -= time[0].tv_sec;
		time[1].tv_usec -= time[0].tv_usec;
printf("%ld %lu is eating\n", time[1].tv_sec * 1000 + time[1].tv_usec / 1000, id);
	//Deinde Filosofare
	}
	else
	{
		printf("%lu died\n", id);
//g_args.deadflag = 1;
	}
	pthread_mutex_unlock(&g_mutex_forks);
//usleep(g_args.time_to_sleep);
	return (NULL);
}

