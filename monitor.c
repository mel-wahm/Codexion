/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 18:42:45 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/30 06:39:32 by q-               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_sim_end(t_config *conf)
{
	int	verdict;

	pthread_mutex_lock(&conf->end_mutex);
	verdict = conf->simulation_ends;
	pthread_mutex_unlock(&conf->end_mutex);
	return (verdict);
}

void	check_ifended(t_config *conf)
{
	int	i;
	int	ended;
	int	idx;

	ended = 1;
	i = 0;
	while (i < conf->number_of_coders)
	{
		pthread_mutex_lock(&conf->coders[i].count_mutex);
		if (conf->coders[i].compile_count < conf->number_of_compiles_required)
			ended = 0;
		pthread_mutex_unlock(&conf->coders[i].count_mutex);
		i++;
	}
	if (ended)
	{
		pthread_mutex_lock(&conf->end_mutex);
		conf->simulation_ends = 1;
		pthread_mutex_unlock(&conf->end_mutex);
		i = 0;
		while (i < conf->number_of_coders)
		{
			idx = conf->coders[i++].right_dongle;
			pthread_mutex_lock(&conf->dongles[idx].available_mutex);
			pthread_cond_broadcast(&conf->dongles[idx].waiters);
			pthread_mutex_unlock(&conf->dongles[idx].available_mutex);
		}
	}
}

void	*monitor_routine(void *args)
{
	t_config	*conf;

	conf = (t_config *)args;
	while (1)
	{
		usleep(500);
		check_ifended(conf);
		if (is_sim_end(conf))
			break ;
	}
	return (NULL);
}
