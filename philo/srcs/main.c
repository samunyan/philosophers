/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:39:25 by samunyan          #+#    #+#             */
/*   Updated: 2023/02/02 16:39:26 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_free(pthread_t *threads, t_philo *philos, t_data *shared)
{
	free(threads);
	free(philos);
	free(shared->fork_locks);
	free(shared->eat_locks);
}

static int	ph_alloc(pthread_t **threads, t_philo **philos, t_data *shared)
{
	*threads = malloc(sizeof(pthread_t) * shared->n_philos);
	*philos = malloc(sizeof(t_philo) * shared->n_philos);
	shared->fork_locks = malloc(sizeof(pthread_mutex_t) * shared->n_philos);
	shared->eat_locks = malloc(sizeof(pthread_mutex_t) * shared->n_philos);
	if (!*threads || !*philos || !shared->fork_locks || !shared->eat_locks)
	{
		ph_free(*threads, *philos, shared);
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data		shared;
	pthread_t	*threads;
	t_philo		*philos;
	int			ret;

	if (!get_args(&shared, argc, argv))
		return (EXIT_FAILURE);
	if (shared.n_meals == 0)
		return (EXIT_SUCCESS);
	if (!ph_alloc(&threads, &philos, &shared))
		return (EXIT_FAILURE);
	if (!ph_init_mutexes(&shared))
	{
		ph_free(threads, philos, &shared);
		return (EXIT_FAILURE);
	}
	if (!ph_threads(threads, philos, &shared) || !ph_destroy_mutexes(&shared))
		ret = EXIT_FAILURE;
	else
		ret = EXIT_SUCCESS;
	ph_free(threads, philos, &shared);
	return (ret);
}
