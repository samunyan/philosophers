/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:36:18 by samunyan          #+#    #+#             */
/*   Updated: 2023/02/02 16:36:20 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared->fork_locks[philo->fork1]));
	print_status(philo, FORK);
	pthread_mutex_lock(&(philo->shared->eat_locks[philo->id]));
	philo->n_forks++;
	pthread_mutex_unlock(&(philo->shared->eat_locks[philo->id]));
	if (philo->shared->n_philos == 1)
	{
		return_forks(philo);
		return (0);
	}
	pthread_mutex_lock(&(philo->shared->fork_locks[philo->fork2]));
	print_status(philo, FORK);
	pthread_mutex_lock(&(philo->shared->eat_locks[philo->id]));
	philo->n_forks++;
	pthread_mutex_unlock(&(philo->shared->eat_locks[philo->id]));
	return (1);
}

void	eat(t_philo *philo)
{
	set_eating_timestamps(philo);
	print_status(philo, EAT);
	pthread_mutex_lock(&(philo->shared->eat_locks[philo->id]));
	philo->n_meals++;
	pthread_mutex_unlock(&(philo->shared->eat_locks[philo->id]));
	ft_usleep(philo->shared->time_to_eat * 1000);
	return_forks(philo);
}

void	return_forks(t_philo *philo)
{
	int	n_forks;

	pthread_mutex_lock(&(philo->shared->eat_locks[philo->id]));
	n_forks = philo->n_forks;
	pthread_mutex_unlock(&(philo->shared->eat_locks[philo->id]));
	if (!n_forks)
		return ;
	pthread_mutex_unlock(&(philo->shared->fork_locks[philo->fork1]));
	if (n_forks == 2)
		pthread_mutex_unlock(&(philo->shared->fork_locks[philo->fork2]));
	pthread_mutex_lock(&(philo->shared->eat_locks[philo->id]));
	philo->n_forks = 0;
	pthread_mutex_unlock(&(philo->shared->eat_locks[philo->id]));
}

void	go_sleep(t_philo *philo)
{
	print_status(philo, SLEEP);
	ft_usleep(philo->shared->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	print_status(philo, THINK);
	ft_usleep(1000);
}
