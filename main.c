/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 01:02:58 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/16 18:51:52 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_config	conf;
	int			valid;

	valid = full_checker(argc, argv, &conf);
	if (valid)
		return (valid);
	valid = initialize_data(&conf);
	if (valid)
		return (valid);
	free(conf.coders);
	free(conf.dongles);
	pthread_mutex_t p;
	pthread_mutex_init(&p, NULL);
	return (0);
}
