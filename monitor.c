/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 18:42:45 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/28 21:33:50 by mel-wahm         ###   ########.fr       */
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

int	check_ifended(t_config *conf)
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
		i = 0;
		while (i < conf->number_of_coders)
		{
			idx = conf->coders[i++].right_dongle;
			pthread_cond_broadcast(&conf->dongles[idx].waiters);
		}
	}
	return (ended);
}
