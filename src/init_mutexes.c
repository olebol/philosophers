/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mutexes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 15:39:39 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/25 15:13:28 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_last_eat_mutexes(t_philo *philos, int amount)
{
	int		i;

	i = 0;
	while (i < amount)
	{
		if (pthread_mutex_init(&philos[i].last_eat_mutex, NULL) != 0)
		{
			destroy_last_eat_mutexes(philos, i);
			ft_error(MUTEX_INIT, 0);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_eat_mutexes(t_philo *philos, int amount)
{
	int		i;

	i = 0;
	while (i < amount)
	{
		if (pthread_mutex_init(&philos[i].eat_mutex, NULL) != 0)
		{
			destroy_eat_mutexes(philos, i);
			ft_error(MUTEX_INIT, 0);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_shared_mutexes(t_shared *shared)
{
	int		i;

	i = 0;
	while (i < SHARED_MUTEXES_SIZE)
	{
		if (pthread_mutex_init(&shared->mutexes[i], NULL) != 0)
		{
			destroy_mutex_array(shared->mutexes, i);
			ft_error(MUTEX_INIT, 0);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_forks(t_shared *shared, int number_of_forks)
{
	t_mutex		*forks;
	int			i;

	forks = (t_mutex *) malloc(number_of_forks * sizeof(t_mutex));
	if (!forks)
		return (0);
	i = 0;
	while (i < number_of_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			destroy_mutex_array(forks, i);
			return (0);
		}
		i++;
	}
	shared->forks = forks;
	return (1);
}
