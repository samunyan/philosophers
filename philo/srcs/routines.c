/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:39:45 by samunyan          #+#    #+#             */
/*   Updated: 2023/02/02 16:39:46 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dining_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	check;

	philo = arg;
	if (pthread_create(&check, NULL, (void *)check_routine, philo) != 0)
	{
		set_error(philo);
		return ;
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!a_philo_died(philo))
	{
		if (!get_forks(philo))
			break ;
		eat(philo);
		if (ate_all_meals(philo))
			break ;
		go_sleep(philo);
		think(philo);
	}
	if (pthread_join(check, NULL) != 0)
		set_error(philo);
}

void	check_routine(void *arg)
{
	t_philo	*philo;
	time_t	now;
	time_t	starvation;

	philo = arg;
	while (!ate_all_meals(philo) && !a_philo_died(philo))
	{
		pthread_mutex_lock(&(philo->shared->eat_locks[philo->id]));
		starvation = philo->starvation_timestamp;
		pthread_mutex_unlock(&(philo->shared->eat_locks[philo->id]));
		now = get_timestamp_since_msec(philo->shared->start_timestamp);
		if (now > starvation)
		{
			print_status(philo, DIE);
			return_forks(philo);
			return ;
		}
		usleep(1000);
	}
}

int	a_philo_died(t_philo *philo)
{
	int	death;

	pthread_mutex_lock(&(philo->shared->death_lock));
	death = philo->shared->dead_philo;
	pthread_mutex_unlock(&(philo->shared->death_lock));
	return (death);
}

int	ate_all_meals(t_philo *philo)
{
	int	n_meals;

	pthread_mutex_lock(&(philo->shared->eat_locks[philo->id]));
	n_meals = philo->n_meals;
	pthread_mutex_unlock(&(philo->shared->eat_locks[philo->id]));
	return (philo->shared->n_meals == n_meals);
}
