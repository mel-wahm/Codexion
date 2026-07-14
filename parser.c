/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 22:01:49 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/14 16:20:43 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	ft_perror(int i)
{
	if (i == 1)
		printf("Error: expected exactly 8 arguments.\n");
	else if (i == 2)
		printf("Error: argument must not be empty.\n");
	else if (i == 3)
		printf("Error: integer overflow.\n");
	else if (i == 4)
		printf("Error: invalid argument.\n");
	else if (i == 5)
		printf("Error: Schedular must be 'edf' or 'fifo'.\n");
	else if (i == 6)
		printf("Error: number of coders should be greater than 0.\n");
	else if (i == 7)
		printf("Error: time to burnout should be greater than 0.\n");
	else if (i == 8)
		printf("Error: time to compile should be greater than 0.\n");
	else if (i == 9)
		printf("Error: time to debug should be greater than 0.\n");
	else if (i == 10)
		printf("Error: time to refactor should be greater than 0.\n");
	else if (i == 11)
		printf("Error: number of compiles required should be greater than 0.\n");
	else if (i == 12)
		printf("Error: dongle cooldown should not be negative.\n");
}

int	config_validator(t_config conf)
{
	if (conf.number_of_coders < 1)
		return (6);
	if (conf.time_to_burnout < 1)
		return (7);
	if (conf.time_to_compile < 1)
		return (8);
	if (conf.time_to_debug < 1)
		return (9);
	if (conf.time_to_refactor < 1)
		return (10);
	if (conf.number_of_compiles_required < 1)
		return (11);
	if (conf.dongle_cooldown < 0)
		return (12);
	return (0);
}

static void	fill_targets(int **targets, t_config *conf)
{
	targets[0] = &conf->number_of_coders;
	targets[1] = &conf->time_to_burnout;
	targets[2] = &conf->time_to_compile;
	targets[3] = &conf->time_to_debug;
	targets[4] = &conf->time_to_refactor;
	targets[5] = &conf->number_of_compiles_required;
	targets[6] = &conf->dongle_cooldown;
}

int	full_checker(int argc, char **argv, t_config *conf)
{
	int	parser_valid;	
	int	config_valid;	

	parser_valid = parser(argc, argv, conf);
	if (parser_valid)
		return (ft_perror(parser_valid), parser_valid);
	config_valid = config_validator(*conf);
	if (config_valid)
		return (ft_perror(config_valid), config_valid);
	return (0);
}

int	parser(int argc, char **argv, t_config *conf)
{
	int	i;
	int	*targets[7];
	int	v;

	i = 0;
	if (argc != 9)
		return (1);
	fill_targets(targets, conf);
	while (++i < 8)
	{
		v = ft_atoi(argv[i], targets[i - 1]);
		if (v)
			return (v);
	}
	if (!strcmp(argv[i], "fifo"))
		conf->scheduler = 0;
	else if (!strcmp(argv[i], "edf"))
		conf->scheduler = 1;
	else
		return (5);
	return (0);
}
