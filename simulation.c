/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 03:02:44 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/26 00:18:57 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*coder(void *args)
{
	t_coder		*c;
	t_config	*conf;
	long		start;
	char 		*string[] = {"is compiling",
							 "is debugging",
							 "is compiling",
							 "has taken a dongle"};

	c = (t_coder *)(args);
	conf = c->conf;
	start = conf->start_time;
	pthread_mutex_lock(&conf->print_mutex);
	printf("coder id: %d\n", c->id);
	pthread_mutex_unlock(&conf->print_mutex);
	// print_state(c, "compiling");
	return (NULL);
}

int	run_simulation(t_config *conf)
{
	t_coder	*coders;
	int		i;
	int		j;
	int		valid;
	long	start_time;

	coders = conf->coders;
	valid = 0;
	i = 0;
	j = 0;
	
	conf->start_time = current_time();
	while (i < conf->number_of_coders)
	{
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
