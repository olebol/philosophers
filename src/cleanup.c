/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 15:32:59 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/26 13:49:39 by opelser       ########   odam.nl         */
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

void	cleanup(t_philo *philos, t_shared *shared)
{
	destroy_mutex_array(shared->forks, shared->amount_of_philos);
	destroy_mutex_array(shared->mutexes, SHARED_MUTEXES_SIZE);
	destroy_eat_mutexes(philos, shared->amount_of_philos);
	destroy_last_eat_mutexes(philos, shared->amount_of_philos);
	free(philos);
}
