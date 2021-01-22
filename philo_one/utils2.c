/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:44:50 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/01/22 12:25:49 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	ft_add_char(char **strdir, char c)
{
	int		size;
	int		i;
	char	*temp;

	size = ft_strlen(*strdir);
	temp = malloc(sizeof(char) * (size + 2));
	temp[size + 1] = '\0';
	i = -1;
	while (++i < size)
		temp[i] = *(*strdir + i);
	temp[i] = c;
	free(*strdir);
	*strdir = temp;
}

static void	ft_putnbr(char **result, unsigned long n)
{
	if (n >= 10)
		ft_putnbr(result, n / 10);
	ft_add_char(result, n % 10 + 48);
}

char		*ft_ultoa(unsigned long n)
{
	char	*result;

	result = malloc(sizeof(char) * 1);
	memset(result, 0, 1);
	ft_putnbr(&result, n);
	return (result);
}

char	*ft_ldtoa(long double n)
{
	char			*result;
	unsigned long	integer_part;
	long double		float_part;

	result = malloc(sizeof(char) * 1);
	memset(result, 0, 1);
	integer_part = (unsigned long)n;
	ft_putnbr(&result, integer_part);
	ft_add_char(&result, '.');
	float_part = n - integer_part;
	integer_part = (unsigned long)(float_part * 10000000000000000000ul);
	ft_putnbr(&result, integer_part);
	return (result);
}
