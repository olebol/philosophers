/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 15:38:50 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/25 20:59:46 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (!print_update(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	if (!print_update(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	return (1);
}

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static int	eat(t_philo *philo)
{
	if (!lock_forks(philo))
		return (0);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->time_last_eat = get_time();
	pthread_mutex_unlock(&philo->last_eat_mutex);
	if (!print_update(philo, "is eating"))
	{
		unlock_forks(philo);
		return (0);
	}
	if (philo->shared->times_to_eat)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->eat_mutex);
	}
	ft_sleep(philo->shared->eat_time);
	unlock_forks(philo);
	return (1);
}

static bool	should_start(t_shared *shared)
{
	int		created;

	pthread_mutex_lock(&shared->mutexes[SHOULD_START]);
	created = shared->philos_created;
	pthread_mutex_unlock(&shared->mutexes[SHOULD_START]);
	if (created != shared->number_of_philos)
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
		usleep(500);
	while (1)
	{
		if (!print_update(philo, "is thinking"))
			break ;
		if (!eat(philo))
			break ;
		if (!print_update(philo, "is sleeping"))
			break ;
		ft_sleep(philo->shared->sleep_time);
	}
	return (NULL);
}
