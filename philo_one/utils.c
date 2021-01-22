/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:12:29 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/01/22 10:59:34 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int							ft_strlen(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
		;
	return (i);
}

char						*ft_strchr(char *str, int c)
{
	int		i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (str + i);
	return (0);
}

unsigned long				ft_atoul(char *str)
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

static long double	pow(long double base, unsigned int exp)
{
	long double result;

	if (exp == 0)
		return (1);
	else
		return (base * pow(base, exp - 1));
}

long double		ft_atold(char *str)
{
	long double	result;
	int			i;
	char		*comma_pos;
	
	if (!str)
		return (0);
	result = 0;
	i = -1;
	comma_pos = ft_strchr(str, '.');
	while (str[++i])
	{
		if ((str[i] >= '0') && (str[i] <= '9')
			&& ((comma_pos > str + i) || !(comma_pos)))
			result = result * 10 + (str[i] - '0');
		else if ((str[i] >= '0') && (str[i] <= '9') && (comma_pos < str + i))
			result += pow(0.1, str + i - comma_pos) * (str[i] - '0');
		else if ((str[i] == '.') && (str + i == comma_pos))
			continue ;
		else
			return (0);
	}
	return (result);
}
