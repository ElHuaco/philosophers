/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:17:20 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/09 12:41:50 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		are_satiated(t_shared *data)
{
	unsigned long	i;

	i = 0;
	while (i < g_args.num_phi)
	{
		if (sem_wait(data->sem_meals[i++]) == -1)
			exit(1);
	}
	sem_post(data->sem_dead);
	exit(0);
}
