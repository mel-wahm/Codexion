/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 08:46:52 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/21 21:45:35 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static	void	*coder_routine(void *args)
{
	t_coder *coder = (t_coder*)(args);
	printf("coder id: %d - right dongle %d - left dongle %d\n", 
	coder->id, coder->right_dongle, coder->left_dongle);
}

static	int	create_threads(t_config *conf, int *idx)
{
	int	i;
	int	valid;
	
	i = 0;
	while (i < conf->number_of_coders)
	{
		valid = pthread_create(&(conf->coders[i].thread), NULL,
		coder_routine, &conf->coders[i]);
		if (valid)
		return (*idx = i, valid);
		i++;
	}
	return (0);
}

int	run_simulation(t_config *conf)
{
	int			valid;
	int			i;
	int			idx;
	idx = conf->number_of_coders;
	i = 0;
	valid = create_threads(conf, &idx);
	while (i < idx)
		pthread_join(conf->coders[i++].thread, NULL);
	if (valid)
	{
		valid = 0;
		while (valid < idx)
			pthread_mutex_destroy(&conf->dongles[valid++].available_mutex);
		return (14);
	}
	return (0);
}
