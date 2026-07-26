/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 13:24:20 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/23 03:30:40 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	clean_data(t_config *conf)
{
	int	i;

	pthread_mutex_init();
	i = 0;
	free(conf->coders);
	while (i < conf->number_of_coders)
		pthread_mutex_destroy(&conf->dongles[i++].available_mutex);
	pthread_mutex_destroy(&conf->end_mutex);
	pthread_mutex_destroy(&conf->print_mutex);
	free(conf->dongles);
}
