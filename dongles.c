/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 21:46:21 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/26 00:39:01 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	taking_dongle(t_coder *coder, t_config *conf)
{
	t_dongle *dongle;
	if (coder->id < conf->number_of_coders)
	dongle = &conf->dongles[coder->left_dongle];
	else
	dongle = &conf->dongles[coder->right_dongle];
	pthread_mutex_lock(&dongle->available_mutex);
	if (dongle->is_available)
	{
		print_state(coder, "Has taken a dongle");
		printf("coder number %d has taken dongle number %d\n", coder->id, dongle->id);
	}
	dongle->is_available = 0;
	pthread_mutex_unlock(&dongle->available_mutex);
}

int	dongle_logic(t_coder *coder)
{
	t_dongle	*right;
	t_dongle	*left;

	right = &coder->conf->dongles[coder->right_dongle];
	left = &coder->conf->dongles[coder->left_dongle];
}
