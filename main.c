/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 01:02:58 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/17 10:40:08 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void destroy_mutexes(t_config *conf)
{
	int	i;

	i = 0;
	while(i < conf->number_of_coders)
		pthread_mutex_destroy(&conf->dongles[i++].available_mutex);
	pthread_mutex_destroy(&conf->end_mutex);
	pthread_mutex_destroy(&conf->print_mutex);
}

int	main(int argc, char **argv)
{
	t_config	conf;
	int			valid;

	conf.coders = NULL;
	conf.dongles = NULL;
	valid = full_checker(argc, argv, &conf);
	if (valid)
		return (valid);
	valid = initialize_data(&conf);
	if (valid)
		return (free(conf.coders), free(conf.dongles), valid);
	valid = run_simulation(&conf);
	if (valid)
		return(valid);
	destroy_mutexes(&conf);
	return (free(conf.coders), free(conf.dongles), 0);
}
