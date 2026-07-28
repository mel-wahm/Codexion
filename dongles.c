/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 21:46:21 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/28 21:37:53 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_t	*mtx;

	mtx = &dongle->available_mutex;
	pthread_mutex_lock(mtx);
	dongle->time_of_last_released = current_time();
	dongle->is_available = 1;
	pthread_cond_signal(&dongle->waiters);
	pthread_mutex_unlock(mtx);
}

int	taking_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_t	*mutex;
	pthread_cond_t	*signal;
	t_config		*conf;

	conf = coder->conf;
	signal = &dongle->waiters;
	mutex = &dongle->available_mutex;
	pthread_mutex_lock(mutex);
	while (!dongle->is_available && !(is_sim_end(conf)))
		pthread_cond_wait(signal, mutex);
	if (is_sim_end(conf))
		return (pthread_mutex_unlock(mutex), 1);
	dongle->is_available = 0;
	pthread_mutex_unlock(mutex);
	print_state(coder, "has taken a dongle.");
	return (0);
}

int	dongle_logic(t_coder *coder)
{
	t_config	*conf;
	int			took;

	conf = coder->conf;
	if (coder->id != conf->number_of_coders)
	{
		took = taking_dongle(coder, &conf->dongles[coder->left_dongle]);
		if (took)
			return (1);
		took = taking_dongle(coder, &conf->dongles[coder->right_dongle]);
		if (took)
			return (release_dongle(&conf->dongles[coder->left_dongle]), 1);
	}
	else
	{
		took = taking_dongle(coder, &conf->dongles[coder->right_dongle]);
		if (took)
			return (1);
		took = taking_dongle(coder, &conf->dongles[coder->left_dongle]);
		if (took)
			return (release_dongle(&conf->dongles[coder->right_dongle]), 1);
	}
	return (0);
}
