/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 21:46:21 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/31 06:33:00 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	taking_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_t	*mtx;

	mtx = &dongle->available_mutex;
	pthread_mutex_lock(mtx);
	while ((!dongle->is_available || dongle->heap.nodes[0].id != coder->id)
		&& !is_sim_end(coder->conf))
		pthread_cond_wait(&dongle->waiters, mtx);
	handle_cooldown(coder, dongle);
	if (is_sim_end(coder->conf))
		return (pthread_mutex_unlock(mtx), 1);
	heap_pop(&dongle->heap, coder->conf->scheduler);
	dongle->is_available = 0;
	pthread_mutex_unlock(mtx);
	print_state(coder, "has taken a dongle");
	return (0);
}

int	dongle_logic(t_coder *coder)
{
	t_config	*conf;
	t_request	req;
	int			took;

	conf = coder->conf;
	if (conf->number_of_coders == 1)
	{
		ft_usleep(conf->time_to_burnout, conf);
		return (1);
	}
	req.id = coder->id;
	req.enter_time = current_time();
	pthread_mutex_lock(&coder->count_mutex);
	req.time_to_burnout = coder->last_compile_time + conf->time_to_burnout;
	pthread_mutex_unlock(&coder->count_mutex);
	push_request(coder, &conf->dongles[coder->left_dongle], &req);
	push_request(coder, &conf->dongles[coder->right_dongle], &req);
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
