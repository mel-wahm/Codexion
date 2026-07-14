/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 00:54:21 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/09 17:47:08 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

int	ft_atoi(const char *str, int *result)
{
	int		i;
	long	number;
	int		sign;

	sign = 1;
	i = 0;
	number = 0;
	if (!str[i])
		return (2);
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (4);
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i++] - '0');
		if (number * sign > 2147483647 || number * sign < -2147483648)
			return (3);
	}
	if (str[i])
		return (4);
	*result = number * sign;
	return (0);
}
