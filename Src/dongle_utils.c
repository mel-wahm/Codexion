/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: q- <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 06:43:24 by q-                #+#    #+#             */
/*   Updated: 2026/07/31 08:05:30 by q-               ###   ########.fr       */
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

void	push_request(t_coder *coder, t_dongle *dongle, t_request *req)
{
	pthread_mutex_lock(&dongle->available_mutex);
	heap_push(&dongle->heap, req, coder->conf->scheduler);
	pthread_mutex_unlock(&dongle->available_mutex);
}

void	handle_cooldown(t_coder *coder, t_dongle *dongle)
{
	long	passed;

	if (dongle->time_of_last_released > 0)
	{
		passed = current_time() - dongle->time_of_last_released;
		if (passed < coder->conf->dongle_cooldown)
			ft_usleep(coder->conf->dongle_cooldown - passed, coder->conf);
	}
}

void	prepare_and_push_requests(t_coder *coder)
{
	t_config	*conf;
	t_request	req;

	conf = coder->conf;
	req.id = coder->id;
	req.enter_time = current_time();
	pthread_mutex_lock(&coder->count_mutex);
	req.time_to_burnout = coder->last_compile_time + conf->time_to_burnout;
	pthread_mutex_unlock(&coder->count_mutex);
	push_request(coder, &conf->dongles[coder->left_dongle], &req);
	push_request(coder, &conf->dongles[coder->right_dongle], &req);
}
