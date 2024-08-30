/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:39:54 by samunyan          #+#    #+#             */
/*   Updated: 2023/02/02 16:39:55 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_timestamp_since_msec(time_t start)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000) - start);
}

static time_t	get_timestamp_usec(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000000) + tp.tv_usec);
}

void	ft_usleep(time_t ms)
{
	time_t	start;

	start = get_timestamp_usec();
	while (get_timestamp_usec() - start < ms)
		usleep(100);
}
