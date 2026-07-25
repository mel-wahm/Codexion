/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 03:02:44 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/24 03:59:28 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*coder(void *args)
{
	t_coder	*c;

	c = (t_coder *)(args);
	printf("Hello from coder %d\n", c->id);
	return (NULL);
}

int	run_simulation(t_config *conf)
{
	t_coder	*coders;
	int		i;
	int		j;
	int		valid;

	coders = conf->coders;
	valid = 0;
	i = 0;
	j = 0;
	while (i < conf->number_of_coders)
	{
		coder_state(&conf->coders[i], i % 3);
		valid = pthread_create(&conf->coders[i].thread,
				NULL, coder, &conf->coders[i]);
		if (valid)
		{
			valid = 14;
			break ;
		}
		i++;
	}
	j = 0;
	while (j < i)
		pthread_join(conf->coders[j++].thread, NULL);
	return (valid);
}
