/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 09:13:01 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/11 11:39:56 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

unsigned long	get_timestamp(struct timeval *t1, struct timeval *t2)
{
	return ((unsigned long)((t2->tv_sec - t1->tv_sec) * 1000)
		+ (unsigned long)((t2->tv_usec - t1->tv_usec) / 1000));
}

void			init_timestamps(struct timeval **time, t_monitor *data)
{
	gettimeofday(*time, NULL);
	data->time_zero = *time;
	gettimeofday(*time + 1, NULL);
	data->time_eat = *time + 1;
	gettimeofday(*time + 2, NULL);
}

void			new_usleep(struct timeval *time, unsigned long time_lapse)
{
	unsigned long	time_objective;
	unsigned long	current_time;

	gettimeofday(time + 2, NULL);
	current_time = get_timestamp(time, time + 2);
	time_objective = current_time + time_lapse;
	while (current_time < time_objective)
	{
		usleep(10);
		gettimeofday(time + 2, NULL);
		current_time = get_timestamp(time, time + 2);
	}
}
