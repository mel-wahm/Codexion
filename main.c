/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 01:02:58 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/24 04:00:32 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_config	conf;
	int			valid;

	valid = 0;
	memset(&conf, 0, sizeof(t_config));
	valid = full_checker(argc, argv, &conf);
	if (valid)
		return (ft_perror(valid), valid);
	valid = initialize_data(&conf);
	if (valid)
		return (ft_perror(valid), valid);
	valid = run_simulation(&conf);
	return (ft_perror(valid), clean_data(&conf), valid);
}
