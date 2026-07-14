/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 11:30:41 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/14 16:34:13 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>

typedef struct s_dongle
{
	int id;
	int availabe;
	pthread_mutex_t mutex;
}	t_dongle;

typedef struct s_coder
{
	int id;
	int time_of_last_compile;
	t_dongle	left_dongle; 
	t_dongle	right_dongle;
	pthread_t thread;
}	t_coder;

typedef struct s_config
{
	int	number_of_coders;
	int	time_to_burnout;
	int	time_to_compile;
	int	time_to_debug;
	int	time_to_refactor;
	int	number_of_compiles_required;	
	int	dongle_cooldown;	
	int	scheduler;
	t_coder **coders;
	t_dongle **dongles;

}	t_config;


int		parser(int argc, char **argv, t_config *conf);
int		config_validator(t_config conf);
int		full_checker(int argc, char **argv, t_config *conf);
int		ft_atoi(const char *str, int *result);
void	ft_perror(int i);

#endif
