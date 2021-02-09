/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:12:29 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/09 09:32:37 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int				ft_strlen(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
		;
	return (i);
}

unsigned long	ft_atoul(char *str)
{
	unsigned long	result;
	int				i;

	if (!str)
		return (0);
	result = 0;
	i = -1;
	while (str[++i])
	{
		if ((str[i] >= '0') && (str[i] <= '9'))
			result = result * 10 + (str[i] - '0');
		else
			return (0);
	}
	return (result);
}

static void		ft_putnbr(char *result, unsigned long n, int pos)
{
	if (n >= 10)
		ft_putnbr(result, n / 10, pos - 1);
	result[pos] = n % 10 + '0';
}

char			*ft_ultoa(unsigned long n)
{
	char			*result;
	int				digit_num;
	unsigned long	temp;

	temp = n;
	digit_num = 1;
	while (temp >= 10)
	{
		temp = temp / 10;
		digit_num++;
	}
	result = malloc(sizeof(char) * (digit_num + 1));
	result[digit_num] = '\0';
	ft_putnbr(result, n, digit_num - 1);
	return (result);
}

void			printchange(unsigned long tm, unsigned long id, char *s)
{
	char		*time_str;
	char		*id_str;
	sem_t		*sem_stdio;

	if ((g_args.deadflag) || ((g_args.num_must_eat)
		&& (g_args.num_satiated == g_args.num_phi)))
		return ;
	sem_stdio = sem_open("stdio", 0);
	time_str = ft_ultoa(tm);
	id_str = ft_ultoa(id + 1);
	sem_wait(sem_stdio);
	write(1, time_str, ft_strlen(time_str));
	write(1, " ", 1);
	write(1, id_str, ft_strlen(id_str));
	write(1, " ", 1);
	write(1, s, ft_strlen(s));
	sem_post(sem_stdio);
	free(id_str);
	free(time_str);
	sem_close(sem_stdio);
}
