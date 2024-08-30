/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:39:54 by samunyan          #+#    #+#             */
/*   Updated: 2023/02/02 16:39:55 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	print_status(t_philo *philo, char *status)
{
	time_t	time;

	pthread_mutex_lock(&(philo->shared->print_lock));
	if (!a_philo_died(philo))
	{
		time = get_timestamp_since_msec(philo->shared->start_timestamp);
		printf("%ld %d %s\n", time, philo->id + 1, status);
		if (ft_strncmp(status, DIE, ft_strlen(DIE)) == 0)
			set_death(philo);
	}
	pthread_mutex_unlock(&(philo->shared->print_lock));
}

void	set_error(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared->death_lock));
	philo->shared->dead_philo = true;
	philo->shared->error = true;
	pthread_mutex_unlock(&(philo->shared->death_lock));
}

void	set_death(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared->death_lock));
	philo->shared->dead_philo = true;
	pthread_mutex_unlock(&(philo->shared->death_lock));
}

void	set_eating_timestamps(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared->eat_locks[philo->id]));
	philo->last_meal_timestamp
		= get_timestamp_since_msec(philo->shared->start_timestamp);
	philo->starvation_timestamp = philo->last_meal_timestamp
		+ philo->shared->time_to_die;
	pthread_mutex_unlock(&(philo->shared->eat_locks[philo->id]));
}
