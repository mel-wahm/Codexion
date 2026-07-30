/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 21:46:21 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/30 18:00:00 by mel-wahm         ###   ########.fr       */
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

	conf = coder->conf;
	signal = &dongle->waiters;
	mutex = &dongle->available_mutex;
	pthread_mutex_lock(mutex);
	while ((!dongle->is_available || dongle->heap.nodes[0].id != coder->id)
		&& !(is_sim_end(conf)))
		pthread_cond_wait(signal, mutex);
	if (dongle->time_of_last_released > 0)
	{
		passed = current_time() - dongle->time_of_last_released;
		if (passed < conf->dongle_cooldown)
		{
			pthread_mutex_unlock(mutex);
			ft_usleep(conf->dongle_cooldown - passed, conf);
			pthread_mutex_lock(mutex);
		}
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
	t_request	req;
	t_dongle	*dongle1;
	t_dongle	*dongle2;

	conf = coder->conf;
	dongle1 = &conf->dongles[coder->right_dongle];
	dongle2 = &conf->dongles[coder->left_dongle];
	pthread_mutex_lock(&dongle1->available_mutex);
	req.id = coder->id;
	req.enter_time = current_time();
	pthread_mutex_lock(&coder->count_mutex);
	req.time_to_burnout = coder->last_compile_time + conf->time_to_burnout;
	pthread_mutex_unlock(&coder->count_mutex);
	heap_push(&dongle1->heap, &req, conf->scheduler);
	pthread_mutex_unlock(&dongle1->available_mutex);
	pthread_mutex_lock(&dongle2->available_mutex);
	req.id = coder->id;
	req.enter_time = current_time();
	pthread_mutex_lock(&coder->count_mutex);
	req.time_to_burnout = coder->last_compile_time + conf->time_to_burnout;
	pthread_mutex_unlock(&coder->count_mutex);
	heap_push(&dongle2->heap, &req, conf->scheduler);
	pthread_mutex_unlock(&dongle2->available_mutex);
	if (conf->number_of_coders == 1)
	{
		taking_dongle(coder, &conf->dongles[0]);
		ft_usleep(conf->time_to_burnout, conf);
		return (1);
	}
	if (coder->id % 2)
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
