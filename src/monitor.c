/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 15:22:19 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/26 13:49:39 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_any_philosopher_dead(t_shared *shared, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < shared->amount_of_philos)
	{
		pthread_mutex_lock(&philos[i].last_eat_mutex);
		if (get_time() - philos[i].time_last_eat > (t_llu) shared->death_time)
		{
			pthread_mutex_unlock(&philos[i].last_eat_mutex);
			print_update(&philos[i], "died");
			return (true);
		}
		pthread_mutex_unlock(&philos[i].last_eat_mutex);
		i++;
	}
	return (false);
}

static bool	is_everyone_full(t_shared *shared, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < shared->amount_of_philos)
	{
		pthread_mutex_lock(&philos[i].eat_mutex);
		if (philos[i].times_eaten < shared->times_to_eat)
		{
			pthread_mutex_unlock(&philos[i].eat_mutex);
			return (false);
		}
		pthread_mutex_unlock(&philos[i].eat_mutex);
		i++;
	}
	return (true);
}

int	monitor(t_shared *shared, t_philo *philos)
{
	usleep(shared->death_time / 2 * 100);
	while (1)
	{
		if (is_any_philosopher_dead(shared, philos) == true)
		{
			pthread_mutex_lock(&shared->mutexes[SHOULD_STOP]);
			shared->should_stop = true;
			pthread_mutex_unlock(&shared->mutexes[SHOULD_STOP]);
			return (0);
		}
		if (shared->times_to_eat && is_everyone_full(shared, philos) == true)
		{
			pthread_mutex_lock(&shared->mutexes[SHOULD_STOP]);
			shared->should_stop = true;
			pthread_mutex_unlock(&shared->mutexes[SHOULD_STOP]);
			return (1);
		}
		usleep(250);
	}
	return (1);
}
