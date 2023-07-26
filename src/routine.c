/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 15:38:50 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/26 13:49:39 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_update(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_update(philo, "has taken a fork");
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->time_last_eat = get_time();
	pthread_mutex_unlock(&philo->last_eat_mutex);
	print_update(philo, "is eating");
	if (philo->shared->times_to_eat)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->eat_mutex);
	}
	ft_sleep(philo->shared->eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static bool	should_start(t_shared *shared)
{
	int		created;

	pthread_mutex_lock(&shared->mutexes[SHOULD_START]);
	created = shared->philos_created;
	pthread_mutex_unlock(&shared->mutexes[SHOULD_START]);
	if (created != shared->amount_of_philos)
		return (false);
	return (true);
}

void	*routine(void *data)
{
	t_philo		*philo;

	philo = (t_philo *) data;
	if (should_start(philo->shared) == false)
		return (NULL);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->time_last_eat = get_time();
	pthread_mutex_unlock(&philo->last_eat_mutex);
	if (philo->id % 2)
	{
		print_update(philo, "is thinking");
		usleep((philo->shared->eat_time / 2) * 1000);
	}
	while (!should_stop(philo->shared))
	{
		eat(philo);
		print_update(philo, "is sleeping");
		ft_sleep(philo->shared->sleep_time);
		print_update(philo, "is thinking");
	}
	return (NULL);
}
