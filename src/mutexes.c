/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutexes.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 15:39:39 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/20 18:31:45 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	destroy_all_mutexes(t_mutex *mutexes, int amount)
{
	int		i;

	i = 0;
	while (i < amount)
	{
		pthread_mutex_destroy(&mutexes[i]);
		i++;
	}
}

int	init_eat_mutexes(t_philo *philos, int amount)
{
	int		i;

	i = 0;
	while (i < amount)
	{
		if (pthread_mutex_init(&philos[i].eat_mutex, NULL) != 0)
		{
			// todo: destroy all prev eat_mutexes
			ft_error(NULL, MUTEX_INIT);
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
			destroy_all_mutexes(shared->mutexes, i);
			ft_error(NULL, MUTEX_INIT);
			return (0);
		}
		i++;
	}
	return (1);
}

t_mutex	*init_forks(int	number_of_forks)
{
	t_mutex	*forks;
	int		i;

	forks = (t_mutex *) malloc(number_of_forks * sizeof(t_mutex));
	if (!forks)
		return (NULL);

	i = 0;
	while (i < number_of_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			destroy_all_mutexes(forks, i);
			return (NULL);
		}
		i++;
	}
	return (forks);
}
