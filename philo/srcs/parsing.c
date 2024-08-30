/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:39:33 by samunyan          #+#    #+#             */
/*   Updated: 2023/02/02 16:39:34 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	data_is_valid(t_data *data, int argc)
{
	if (data->n_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || (argc == 6 && data->n_meals < 0))
		return (0);
	return (1);
}

static int	str_is_int(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	init_data(t_data *data, int argc, char *argv[])
{
	memset(data, 0, sizeof(t_data));
	data->n_philos = ft_atoi(argv[1]);
	if (!ft_atoi_is_valid(data->n_philos, argv[1]))
		return (0);
	data->time_to_die = ft_atoi(argv[2]);
	if (!ft_atoi_is_valid(data->time_to_die, argv[2]))
		return (0);
	data->time_to_eat = ft_atoi(argv[3]);
	if (!ft_atoi_is_valid(data->time_to_eat, argv[3]))
		return (0);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (!ft_atoi_is_valid(data->time_to_sleep, argv[4]))
		return (0);
	if (argc == 6)
	{
		data->n_meals = ft_atoi(argv[5]);
		if (!ft_atoi_is_valid(data->n_meals, argv[5]))
			return (0);
	}
	else
		data->n_meals = -1;
	return (1);
}

int	get_args(t_data *data, int argc, char *argv[])
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Error : wrong arguments\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!str_is_int(argv[i]))
		{
			printf("Error : wrong arguments\n");
			return (0);
		}
		i++;
	}
	if (!init_data(data, argc, argv) || !data_is_valid(data, argc))
	{
		printf("Error : wrong arguments\n");
		return (0);
	}
	return (1);
}
