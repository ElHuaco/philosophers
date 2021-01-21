/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:13:18 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/01/21 19:49:44 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	print_status_change(struct timeval *t, unsigned long id, char *str)
{
	unsigned long double		time;
	char						*time_str;
	char						*id_str;

//Importancia de ultoa, uldtoa eficaces -> ∆t <= 10 ms entre muerte y print.
	gettimeofday(t + 1, NULL);
	t[1].tv_sec -= t[0].tv_sec;
	t[1].tv_usec -= t[0].tv_usec;
	time = t[1].tv_sec * 1000.0 + t[1].tv_usec / 1000.0;
	time_str = ft_uldtoa(time);
	id_str = ft_ultoa(id);
	pthread_mutex_lock(&g_mutex_stdout);
	write(1, time_str, ft_strlen(time_str));
	write(1, " ", 1);
	write(1, id_str, ft_strlen(id_str));
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&g_mutex_stdout);
	free(time_str);
	free(id_str);
}

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

