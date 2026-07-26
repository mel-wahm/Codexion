/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 00:54:21 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/26 00:37:16 by mel-wahm         ###   ########.fr       */
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

long	current_time(void)
{
	struct timeval	time;
	long			t;

	gettimeofday(&time, NULL);
	t = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (t);
}

void	print_state(t_coder *coder, char *state)
{
	t_config		*conf;
	long			time;

	conf = coder->conf;
	pthread_mutex_lock(&conf->print_mutex);
	time = current_time() - conf->start_time;
	// exit(0);
	printf("%ld %d %s\n", time, coder->id, state);
	pthread_mutex_unlock(&conf->print_mutex);
}
