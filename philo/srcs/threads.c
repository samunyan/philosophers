/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:39:49 by samunyan          #+#    #+#             */
/*   Updated: 2023/02/02 16:39:50 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, int n_philos)
{
	if (philo->id % 2 == 0)
	{
		if (philo->id == n_philos - 1)
		{
			philo->fork1 = philo->id;
			philo->fork2 = 0;
			return ;
		}
		philo->fork1 = philo->id;
		philo->fork2 = philo->id + 1;
		return ;
	}
	if (philo->id == n_philos - 1)
	{
		philo->fork1 = 0;
		philo->fork2 = philo->id;
		return ;
	}
	philo->fork1 = philo->id + 1;
	philo->fork2 = philo->id;
}

static void	ph_init_philos(t_philo *philos, t_data *shared)
{
	int		i;

	i = 0;
	while (i < shared->n_philos)
	{
		memset(&philos[i], 0, sizeof(t_philo));
		philos[i].id = i;
		philos[i].shared = shared;
		assign_forks(&philos[i], shared->n_philos);
		set_eating_timestamps(&philos[i]);
		i++;
	}
}

int	ph_threads(pthread_t *threads, t_philo *philos, t_data *shared)
{
	int	i;
	int	error;

	i = 0;
	error = false;
	shared->start_timestamp = get_timestamp_since_msec(0);
	ph_init_philos(philos, shared);
	while (i < philos->shared->n_philos)
	{
		if (pthread_create(&threads[i], NULL, (void *)dining_routine,
				&philos[i]) != 0)
		{
			error = true;
			break ;
		}
		i++;
	}
	while (i)
	{
		if (pthread_join(threads[i - 1], NULL) != 0)
			error = true;
		i--;
	}
	return (!error && !shared->error);
}
