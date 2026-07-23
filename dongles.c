/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 21:46:21 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/23 02:52:47 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	taking_dongle(t_dongle *dongle, t_config *conf)
{
	pthread_mutex_lock(&dongle->available_mutex);
}

int	dongle_logic(t_coder *coder)
{
	t_dongle	*right;
	t_dongle	*left;

	right = &coder->conf->dongles[coder->right_dongle];
	left = &coder->conf->dongles[coder->left_dongle];
}
