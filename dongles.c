/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 21:46:21 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/30 08:55:20 by q-               ###   ########.fr       */
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
	pthread_cond_broadcast(&dongle->waiters);
	pthread_mutex_unlock(mtx);
}

int	taking_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_t	*mutex;
	pthread_cond_t	*signal;
	t_config		*conf;
	long			passed;
	t_request		req;

	conf = coder->conf;
	signal = &dongle->waiters;
	mutex = &dongle->available_mutex;
	pthread_mutex_lock(mutex);
	req.id = coder->id;
	req.enter_time = current_time();
	pthread_mutex_lock(&coder->count_mutex);
	req.time_to_burnout = coder->last_compile_time + conf->time_to_burnout;
	pthread_mutex_unlock(&coder->count_mutex);
	heap_push(&dongle->heap, &req, conf->scheduler);
	while ((!dongle->is_available || dongle->heap.nodes[0].id != coder->id)
		&& !(is_sim_end(conf)))
		pthread_cond_wait(signal, mutex);
	if (dongle->time_of_last_released > 0)
	{
		passed = current_time() - dongle->time_of_last_released;
		if (passed < conf->dongle_cooldown)
			ft_usleep(conf->dongle_cooldown - passed, conf);
	}
	if (is_sim_end(conf))
		return (pthread_mutex_unlock(mutex), 1);
	heap_pop(&dongle->heap, conf->scheduler);
	dongle->is_available = 0;
	pthread_mutex_unlock(mutex);
	print_state(coder, "has taken a dongle");
	return (0);
}

int	dongle_logic(t_coder *coder)
{
	t_config	*conf;
	int			took;

	conf = coder->conf;
	if (conf->number_of_coders == 1)
	{
		// taking_dongle(coder, &conf->dongles[1]);
		ft_usleep(conf->time_to_burnout, conf);
		return (1);
	}
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
