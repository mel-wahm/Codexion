/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 18:42:45 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/27 19:05:23 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_ifended(t_config *conf)
{
	int	i;
	int	ended;

	ended = 1;
	i = 0;
	while (i < conf->number_of_coders)
	{
		if (conf->coders[i].compile_count < conf->number_of_compiles_required)
			ended = 0;
		i++;
	}
	return (ended);
}
