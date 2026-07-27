/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 21:46:21 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/27 06:55:36 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	taking_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_t	*mutex;
	pthread_cond_t	*signal;
	t_config		*conf;

	conf = coder->conf;
	signal = &dongle->waiters;
	mutex = &dongle->available_mutex;
	pthread_mutex_lock(mutex);
	while (!dongle->is_available && !conf->simulation_ends)
		pthread_cond_wait(signal, mutex);
	dongle->is_available = 0;
	pthread_mutex_unlock(mutex);
	if (conf->simulation_ends)
		return (0);
	print_state(coder, "has taken a dongle.");
	return (0);
}

int	dongle_logic(t_coder *coder)
{
	t_config	*conf;

	conf = coder->conf;
	if (coder->id != conf->number_of_coders)
	{
		taking_dongle(coder, &conf->dongles[coder->left_dongle]);
		taking_dongle(coder, &conf->dongles[coder->right_dongle]);
	}
	else
	{
		taking_dongle(coder, &conf->dongles[coder->right_dongle]);
		taking_dongle(coder, &conf->dongles[coder->left_dongle]);
	}
	return (0);
}
