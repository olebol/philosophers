/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 15:38:50 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/19 16:36:32 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int		print_update(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->shared->mutexes[PRINT_MUTEX]) != 0)
	{
		perror("Mutex locking failed\n");
		return (0);
	}
	printf("%llu\t\t", time_since(philo->shared->start_time));
	printf("update from philo %d\n", philo->id);
	if (pthread_mutex_unlock(&philo->shared->mutexes[PRINT_MUTEX]) != 0)
	{
		perror("Mutex unlocking failed\n");
		return (0);
	}
	return (1);
}

int	philo_loop(t_philo *philo)
{
	if (!print_update(philo))
		return (0);
	sleep(5);
	return (1);
}

void	*routine(void *data)
{
	t_philo		*philo;

	philo = (t_philo *) data;
	printf("%llu\t", time_since(philo->shared->start_time));
	printf("Hello world from philo %d\n", philo->id);
	while (philo->times_eaten < philo->shared->times_to_eat)
	{
		if (!philo_loop(philo))
			return (NULL);
	}
	return ("SUCCES");
}
