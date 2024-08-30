/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:36:23 by samunyan          #+#    #+#             */
/*   Updated: 2023/02/02 16:36:24 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_destroy_mutexes(t_data *shared)
{
	int	error;

	error = 0;
	if (!ph_destroy_single_mutex(&shared->print_lock))
		error = 1;
	if (!ph_destroy_single_mutex(&shared->death_lock))
		error = 1;
	if (!ph_destroy_mutex_array(shared->fork_locks, shared->n_philos))
		error = 1;
	if (!ph_destroy_mutex_array(shared->eat_locks, shared->n_philos))
		error = 1;
	return (!error);
}

int	ph_destroy_single_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex) != 0)
		return (0);
	return (1);
}

int	ph_destroy_mutex_array(pthread_mutex_t *mutex_array, int n_mutexes)
{
	int	error;

	error = 0;
	while (n_mutexes > 0)
	{
		if (pthread_mutex_destroy(&mutex_array[n_mutexes - 1]) != 0)
			error = 1;
		n_mutexes--;
	}
	return (!error);
}
