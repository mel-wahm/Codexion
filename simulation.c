/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: q- <q-@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 03:02:44 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/29 03:12:36 by q-               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*coder(void *args)
{
	t_config	*conf;
	t_coder		*coder;
	int			took;

	took = 0;
	coder = (t_coder *)(args);
	conf = coder->conf;
	if (coder->id % 2)
		usleep(500);
	while (!is_sim_end(conf))
	{
		took = dongle_logic(coder);
		if (took)
			return (NULL);
		pthread_mutex_lock(&coder->count_mutex);
		coder->last_compile_time = current_time();
		pthread_mutex_unlock(&coder->count_mutex);
		print_state(coder, "is compiling");
		ft_usleep(conf->time_to_compile, conf);
		release_dongle(&conf->dongles[coder->right_dongle]);
		release_dongle(&conf->dongles[coder->left_dongle]);
		pthread_mutex_lock(&coder->count_mutex);
		coder->compile_count++;
		pthread_mutex_unlock(&coder->count_mutex);
		if (is_sim_end(conf))
		{
			pthread_mutex_lock(&conf->end_mutex);
			conf->simulation_ends = 1;
			pthread_mutex_unlock(&conf->end_mutex);
		}
		pthread_mutex_lock(&coder->count_mutex);
		if (coder->compile_count == conf->number_of_compiles_required)
			return (pthread_mutex_unlock(&coder->count_mutex), NULL);
		pthread_mutex_unlock(&coder->count_mutex);
		print_state(coder, "is debugging");
		ft_usleep(conf->time_to_debug, conf);
		print_state(coder, "is refactoring");
		ft_usleep(conf->time_to_refactor, conf);
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
	valid = pthread_create(&conf->monitor_thread, NULL, monitor_routine,
			conf);
	if (valid)
		return (14);
	while (i < conf->number_of_coders)
	{
		valid = pthread_create(&coders[i].thread, NULL, coder, &coders[i]);
		if (valid)
		{
			valid = 14;
			pthread_mutex_lock(&conf->end_mutex);
			conf->simulation_ends = 1;
			pthread_mutex_unlock(&conf->end_mutex);
			j = 0;
			while (j < conf->number_of_coders)
			{
				pthread_mutex_lock(&conf->dongles[j].available_mutex);
				pthread_cond_broadcast(&conf->dongles[j].waiters);
				pthread_mutex_unlock(&conf->dongles[j].available_mutex);
				j++;
			}
			break ;
		}
		i++;
	}
	j = 0;
	while (j < i)
		pthread_join(coders[j++].thread, NULL);
	pthread_join(conf->monitor_thread, NULL);
	return (valid);
}
