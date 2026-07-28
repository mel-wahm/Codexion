/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 03:02:44 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/27 19:18:00 by mel-wahm         ###   ########.fr       */
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
	pthread_cond_signal(&dongle->waiters);
	pthread_mutex_unlock(mtx);
}

void	*coder(void *args)
{
	t_config	*conf;
	t_coder		*coder;

	coder = (t_coder *)(args);
	conf = coder->conf;
	if (coder->id % 2)
		usleep(100);
	while (!conf->simulation_ends)
	{
		coder->last_compile_time = current_time();
		coder->compile_count++;
		dongle_logic(coder);
		print_state(coder, "is compiling");
		usleep(conf->time_to_compile * 1000);
		release_dongle(&conf->dongles[coder->right_dongle]);
		release_dongle(&conf->dongles[coder->left_dongle]);
		if (check_ifended(conf))
		{
			pthread_mutex_lock(&conf->end_mutex);
			conf->simulation_ends = 1;
			pthread_mutex_unlock(&conf->end_mutex);
		}
		if (coder->compile_count == conf->number_of_compiles_required)
			return (NULL);
		print_state(coder, "is debugging");
		usleep(conf->time_to_debug * 1000);
		print_state(coder, "is refactoring");
		usleep(conf->time_to_refactor * 1000);
	}
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
	conf->start_time = current_time();
	while (i < conf->number_of_coders)
	{
		valid = pthread_create(&coders[i].thread, NULL, coder, &coders[i]);
		if (valid)
		{
			valid = 14;
			break ;
		}
		i++;
	}
	j = 0;
	while (j < i)
		pthread_join(coders[j++].thread, NULL);
	return (valid);
}
