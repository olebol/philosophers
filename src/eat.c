/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 18:21:44 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/19 23:01:49 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	take_fork(t_philo *philo, int direction)
{
	if (direction == LEFT && pthread_mutex_lock(philo->left_fork) != 0)
	{
		ft_error(NULL, MUTEX_LOCK);
		return (0);
	}
	if (direction == RIGHT && pthread_mutex_lock(philo->right_fork) != 0)
	{
		ft_error(NULL, MUTEX_LOCK);
		return (0);
	}
	print_update(philo, TAKE_FORK);
	return (1);
}

static int	leave_fork(t_philo *philo, int direction)
{
	if (direction == LEFT && pthread_mutex_unlock(philo->left_fork) != 0)
	{
		ft_error(NULL, MUTEX_UNLOCK);
		return (0);
	}
	if (direction == RIGHT && pthread_mutex_unlock(philo->right_fork) != 0)
	{
		ft_error(NULL, MUTEX_UNLOCK);
		return (0);
	}
	return (1);
}

int	eat(t_philo *philo)
{
	// think
	print_update(philo, "is thinking");

	// try to lock forks (put this in a separate function to print when philo takes a fork)
	if (!take_fork(philo, LEFT) || !take_fork(philo, RIGHT))
		return (0);
	
	// eat
	philo->time_last_eat = time_since(philo->shared->start_time);
	print_update(philo, "is eating");
	philo->times_eaten++;
	ft_sleep(philo->shared->eat_time);

	//try to unlock forks
	if (!leave_fork(philo, LEFT) || !leave_fork(philo, RIGHT))
		return (0);

	return (1);
}
