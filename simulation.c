/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 03:02:44 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/23 03:26:26 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*coder(void *args)
{
	t_coder *c = (t_coder *)(args);
	printf("Hello from coder %d\n", c->id);
}

int	run_simulation(t_config *conf)
{
	t_coder *coders = conf->coders;
	int	i;

	i = 0;
	while(i < conf->number_of_coders)
	{
		pthread_create(&conf->coders[i].thread, NULL, coder, &conf->coders[i]);
		pthread_join(conf->coders[i].thread, NULL);
		i++;
	}
}