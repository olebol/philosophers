/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 15:38:50 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/21 23:54:19 by opelser       ########   odam.nl         */
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
}

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static int	eat(t_philo *philo)
{
	if (!print_update(philo, "is thinking"))
		return (0);
	if (lock_forks(philo))
		return (0);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->time_last_eat = get_time();
	pthread_mutex_unlock(&philo->last_eat_mutex);
	if (!print_update(philo, "is eating"))
	{
		unlock_forks();
		return (0);
	}
	if (philo->shared->times_to_eat)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->eat_mutex);
	}
	ft_sleep(philo->shared->eat_time);
	unlock_forks();
	return (1);
}

void	*routine(void *data)
{
	t_philo		*philo;

	philo = (t_philo *) data;
	pthread_mutex_lock(&philo->shared->mutexes[SHOULD_START]);
	pthread_mutex_unlock(&philo->shared->mutexes[SHOULD_START]);
	if (philo->shared->philos_created != philo->shared->number_of_philos)
		return (NULL);
	if (philo->id % 2)
		usleep(200);
	while (1)
	{
		if (!eat(philo))
			return (NULL);
		if (!print_update(philo, "is sleeping"))
			return (NULL);
		ft_sleep(philo->shared->sleep_time);
	}
	return ("SUCCES");
}
