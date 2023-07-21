/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 15:38:50 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/21 16:58:43 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	take_fork(t_philo *philo, int direction)
{
	if (direction == LEFT && pthread_mutex_lock(philo->left_fork) != 0)
	{
		ft_error(NULL, MUTEX_LOCK, 0);
		return (0);
	}
	if (direction == RIGHT && pthread_mutex_lock(philo->right_fork) != 0)
	{
		ft_error(NULL, MUTEX_LOCK, 0);
		return (0);
	}
	print_update(philo, "has taken a fork");
	return (1);
}

static int	leave_fork(t_philo *philo, int direction)
{
	if (direction == LEFT && pthread_mutex_unlock(philo->left_fork) != 0)
	{
		ft_error(NULL, MUTEX_UNLOCK, 0);
		return (0);
	}
	if (direction == RIGHT && pthread_mutex_unlock(philo->right_fork) != 0)
	{
		ft_error(NULL, MUTEX_UNLOCK, 0);
		return (0);
	}
	return (1);
}

static int	eat(t_philo *philo)
{
	// think
	if (!print_update(philo, "is thinking"))
		return (0);
	// try to lock forks
	if (!take_fork(philo, LEFT) || !take_fork(philo, RIGHT))
		return (0);
	
	// eat
	pthread_mutex_lock(&philo->eat_mutex);
	if (!print_update(philo, "is eating"))
	{
		leave_fork(philo, LEFT);
		leave_fork(philo, RIGHT);
		pthread_mutex_unlock(&philo->eat_mutex);
		return (0);
	}
	philo->time_last_eat = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->eat_mutex);
	ft_sleep(philo->shared->eat_time);

	//try to unlock forks
	if (!leave_fork(philo, LEFT) || !leave_fork(philo, RIGHT))
		return (0);

	return (1);
}

static int	philo_loop(t_philo *philo)
{
	if (!eat(philo))
		return (0);
	if (!print_update(philo, "is sleeping"))
		return (0);
	ft_sleep(philo->shared->sleep_time);
	return (1);
}

void	*routine(void *data)
{
	t_philo		*philo;

	philo = (t_philo *) data;
	if (philo->id % 2)
		usleep(200);
	while (1) // todo: this stops them from eating, even if not all of them have finished all their meals yet
	{
		if (!philo_loop(philo))
			return (NULL);
	}
	return ("SUCCES");
}
