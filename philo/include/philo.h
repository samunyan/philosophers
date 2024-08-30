/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:39:39 by samunyan          #+#    #+#             */
/*   Updated: 2023/02/02 16:39:40 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <stdbool.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_data
{
	int				n_philos;
	time_t			start_timestamp;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			time_to_die;
	int				n_meals;
	int				dead_philo;
	int				error;
	pthread_mutex_t	*fork_locks;
	pthread_mutex_t	*eat_locks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
}				t_data;

typedef struct s_philo
{
	int		id;
	t_data	*shared;
	int		fork1;
	int		fork2;
	int		n_forks;
	time_t	last_meal_timestamp;
	time_t	starvation_timestamp;
	int		n_meals;
}				t_philo;

int		get_args(t_data *data, int argc, char *argv[]);

int		ph_threads(pthread_t *threads, t_philo *philos, t_data *shared);

void	dining_routine(void *arg);
void	check_routine(void *arg);
int		a_philo_died(t_philo *philo);
int		ate_all_meals(t_philo *philo);

void	think(t_philo *philo);
int		get_forks(t_philo *philo);
void	eat(t_philo *philo);
void	return_forks(t_philo *philo);
void	go_sleep(t_philo *philo);

time_t	get_timestamp_since_msec(time_t start);
void	ft_usleep(time_t ms);

void	print_status(t_philo *philo, char *status);
void	set_error(t_philo *philo);
void	set_death(t_philo *philo);
void	set_eating_timestamps(t_philo *philo);

int		ph_init_mutexes(t_data *shared);
int		ph_destroy_mutexes(t_data *shared);
int		ph_destroy_single_mutex(pthread_mutex_t *mutex);
int		ph_destroy_mutex_array(pthread_mutex_t *mutex_array, int n_mutexes);

int		ft_atoi(const char *str);
int		ft_atoi_is_valid(int i, const char *str);
int		ft_isdigit(int c);
size_t	ft_get_num_len(unsigned long long n, unsigned int radix);
int		ft_isspace(int c);
char	*ft_skip_space(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif