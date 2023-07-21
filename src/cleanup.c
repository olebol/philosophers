/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 15:32:59 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/21 23:50:18 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_last_eat_mutexes(t_philo *philos, int amount)
{
	int		i;

	i = 0;
	while (i < amount)
	{
		pthread_mutex_destroy(&philos[i].last_eat_mutex);
		i++;
	}
}

void	destroy_eat_mutexes(t_philo *philos, int amount)
{
	int		i;

	i = 0;
	while (i < amount)
	{
		pthread_mutex_destroy(&philos[i].eat_mutex);
		i++;
	}
}

void	destroy_mutex_array(t_mutex *mutexes, int amount)
{
	int		i;

	i = 0;
	while (i < amount)
	{
		pthread_mutex_destroy(&mutexes[i]);
		i++;
	}
}

static void	destroy_forks(t_philo *philos, int amount)
{
	int		i;

	i = 0;
	while (i < amount)
	{
		pthread_mutex_destroy(philos[i].left_fork);
		i++;
	}
}

void	cleanup(t_philo *philos, t_shared *shared)
{
	int		number_of_philos;

	number_of_philos = shared->number_of_philos;
	destroy_mutex_array(shared->mutexes, SHARED_MUTEXES_SIZE);
	destroy_eat_mutexes(philos, shared->number_of_philos);
	destroy_forks(philos, shared->number_of_philos);
	free(philos);
}
