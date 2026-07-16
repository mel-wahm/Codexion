/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-wahm <mel-wahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 11:30:41 by mel-wahm          #+#    #+#             */
/*   Updated: 2026/07/16 18:49:37 by mel-wahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>

typedef struct s_config	t_config;

typedef struct s_dongle
{
	int				id;
	int				time_of_last_released;
	int				is_available;
	pthread_mutex_t	available_mutex;
}	t_dongle;

typedef struct s_coder
{
	int			id;
	int			last_compile_time;
	int			compile_count;
	int			right_dongle;	
	int			left_dongle;
	t_config	*conf;
	pthread_t	thread;

}	t_coder;

typedef struct s_config
{
	int					number_of_coders;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_debug;
	int					time_to_refactor;
	int					number_of_compiles_required;	
	int					dongle_cooldown;	
	int					scheduler;
	pthread_mutex_t		end_mutex;
	pthread_mutex_t		print_mutex;
	int					simulation_ends;
	t_coder				*coders;
	t_dongle			*dongles;
}	t_config;

int		parser(int argc, char **argv, t_config *conf);
int		config_validator(t_config *conf);
int		initialize_data(t_config *conf);
int		full_checker(int argc, char **argv, t_config *conf);
int		ft_atoi(const char *str, int *result);
void	ft_perror(int i);

#endif
