/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 01:02:58 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/21 21:43:43 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_config	conf;
	int			valid;
	
	memset(&conf, 0, sizeof(t_config));
	valid = full_checker(argc, argv, &conf);
	if (valid)
		return (ft_perror(valid), valid); // // // this part is done. 
	valid = initialize_data(&conf);
	if (valid == 21)
		return (ft_perror(valid), valid);
	else if (valid)
		return (ft_perror(valid),
		clean_data(&conf), valid);
	valid = run_simulation(&conf);
	return(ft_perror(valid),
			   clean_data(&conf), valid);
}
