/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:45:56 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/16 18:51:14 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static	int	allocate_memory(t_config *conf)
{
	int	n;

	n = conf->number_of_coders;
	conf->coders = malloc(n * sizeof(t_coder));
	conf->dongles = malloc(n * sizeof(t_dongle));
	if (!conf->coders || !conf->dongles)
		return (12);
	return (0);
}

static	void	init_coders(t_config *conf)
{
	int		i;
	int		n;
	t_coder	tmp;

	n = conf->number_of_coders;
	i = 0;
	while (i < n)
	{
		tmp.id = i + 1;
		tmp.left_dongle = i;
		if (i != n - 1)
			tmp.right_dongle = i + 1;
		else
			tmp.right_dongle = 0;
		tmp.compile_count = 0;
		tmp.last_compile_time = 0;
		tmp.conf = conf;
		conf->coders[i] = tmp;
		i++;
	}
}

static	void	init_dongles(t_config *conf)
{
	t_dongle	tmp;
	int			i;
	int			n;

	i = 0;
	n = conf->number_of_coders;
	while (i < n)
	{
		tmp.id = i;
		tmp.is_available = 1;
		tmp.time_of_last_released = 0;
		conf->dongles[i] = tmp;
		pthread_mutex_init(&conf->dongles[i].available_mutex, NULL);
		i++;
	}
}

int	initialize_data(t_config *conf)
{
	int	valid;

	valid = allocate_memory(conf);
	if (valid)
		return (printf("Allocation Error!"), valid);
	init_coders(conf);
	init_dongles(conf);
	return (0);
}
