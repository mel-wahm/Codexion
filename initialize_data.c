/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:45:56 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/27 05:17:59 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	allocate_memory(t_config *conf)
{
	int	n;

	n = conf->number_of_coders;
	conf->coders = malloc(n * sizeof(t_coder));
	conf->dongles = malloc(n * sizeof(t_dongle));
	if (!conf->coders || !conf->dongles)
		return (16);
	return (0);
}

static void	init_coders(t_config *conf)
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
		tmp.right_dongle = (i + 1) % n;
		tmp.compile_count = 0;
		tmp.last_compile_time = 0;
		tmp.conf = conf;
		conf->coders[i] = tmp;
		i++;
	}
}

static int	init_dongles(t_config *conf)
{
	t_dongle	tmp;
	int			i;
	int			mtx;

	i = 0;
	while (i < conf->number_of_coders)
	{
		tmp.id = i;
		tmp.is_available = 1;
		tmp.time_of_last_released = 0;
		conf->dongles[i] = tmp;
		mtx = pthread_mutex_init(&conf->dongles[i].available_mutex, NULL);
		if (mtx)
		{
			mtx = 0;
			while (mtx < i)
			{
				pthread_mutex_destroy(&conf->dongles[mtx].available_mutex);
				pthread_cond_destroy(&conf->dongles[mtx++].waiters);
			}
			return (1);
		}
		mtx = pthread_cond_init(&conf->dongles[i].waiters, NULL);
		if (mtx)
		{
			mtx = 0;
			while (mtx < i)
			{
				pthread_mutex_destroy(&conf->dongles[mtx].available_mutex);
				pthread_cond_destroy(&conf->dongles[mtx++].waiters);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	initialize_data(t_config *conf)
{
	int	valid;

	valid = pthread_mutex_init(&conf->print_mutex, NULL);
	if (valid)
		return (21);
	valid = pthread_mutex_init(&conf->end_mutex, NULL);
	if (valid)
		return (pthread_mutex_destroy(&conf->print_mutex), 21);
	valid = allocate_memory(conf);
	if (valid)
		return (pthread_mutex_destroy(&conf->print_mutex),
			pthread_mutex_destroy(&conf->end_mutex), free(conf->coders),
			free(conf->dongles), valid);
	init_coders(conf);
	valid = init_dongles(conf);
	if (valid)
		return (pthread_mutex_destroy(&conf->print_mutex),
			pthread_mutex_destroy(&conf->end_mutex), free(conf->coders),
			free(conf->dongles), 22);
	return (0);
}
