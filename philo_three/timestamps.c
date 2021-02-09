/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:13:34 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/09 10:13:55 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
