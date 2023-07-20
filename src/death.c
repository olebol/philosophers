/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 15:22:19 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/20 21:49:03 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_any_philosopher_dead(t_shared *shared, t_philo *philos)
{
	int		i;
	t_llu	time_since_meal;

	i = 0;
	while (i < shared->number_of_philos)
	{
		pthread_mutex_lock(&philos[i].eat_mutex);
		time_since_meal = get_time() - philos[i].time_last_eat;
		// printf("time check: %llu\n", time_since_meal);
		if (time_since_meal > (t_llu) shared->death_time)
		{
			pthread_mutex_unlock(&philos[i].eat_mutex);
			print_update(&philos[i], "died");
			return (true);
		}
		pthread_mutex_unlock(&philos[i].eat_mutex);
		i++;
	}
	return (false);
}

static bool	is_everyone_full(t_shared *shared, t_philo *philos)
{
	int		i;

	i = 0;
	if (shared->times_to_eat == 0)
		return (false);
	while (i < shared->number_of_philos)
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
	pthread_mutex_lock(&shared->mutexes[PRINT]);
	printf("\nAll philosophers have eaten %d times!\n", shared->times_to_eat);
	pthread_mutex_unlock(&shared->mutexes[PRINT]);
	return (true);
}

bool	should_stop(t_shared *shared)
{
	bool	ret;

	// printf("waiting for stop lock\n");
	pthread_mutex_lock(&shared->mutexes[SHOULD_STOP]);
	// printf("no longer waiting for stop lock\n");

	ret = shared->should_stop;

	pthread_mutex_unlock(&shared->mutexes[SHOULD_STOP]);
	return (ret);
}

int	check_for_death_main_thread(t_shared *shared, t_philo *philos)
{
	while (1)
	{
		if (is_any_philosopher_dead(shared, philos) == true)
			break ;
		if (is_everyone_full(shared, philos) == true)
			break ;
	}
	pthread_mutex_lock(&shared->mutexes[SHOULD_STOP]);
	shared->should_stop = true;
	pthread_mutex_unlock(&shared->mutexes[SHOULD_STOP]);
	return (1);
}

