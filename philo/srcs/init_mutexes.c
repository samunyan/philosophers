/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:39:21 by samunyan          #+#    #+#             */
/*   Updated: 2023/02/02 16:39:22 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_init_single_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		return (0);
	return (1);
}

static int	ph_init_mutex_array(pthread_mutex_t *mutex_array, int n_mutexes)
{
	int	i;

	i = 0;
	while (i < n_mutexes)
	{
		if (pthread_mutex_init(&mutex_array[i], NULL) != 0)
		{
			ph_destroy_mutex_array(mutex_array, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ph_init_mutexes(t_data *shared)
{
	if (!ph_init_single_mutex(&shared->print_lock))
		return (0);
	if (!ph_init_single_mutex(&shared->death_lock))
	{
		ph_destroy_single_mutex(&shared->print_lock);
		return (0);
	}
	if (!ph_init_mutex_array(shared->fork_locks, shared->n_philos))
	{
		ph_destroy_single_mutex(&shared->print_lock);
		ph_destroy_single_mutex(&shared->death_lock);
		return (0);
	}
	if (!ph_init_mutex_array(shared->eat_locks, shared->n_philos))
	{
		ph_destroy_single_mutex(&shared->print_lock);
		ph_destroy_single_mutex(&shared->death_lock);
		ph_destroy_mutex_array(shared->eat_locks, shared->n_philos);
		return (0);
	}
	return (1);
}
