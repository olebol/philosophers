/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 18:17:06 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/26 14:30:14 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_update(t_philo *philo, char *str)
{
	t_llu		time;

	pthread_mutex_lock(&philo->shared->mutexes[PRINT]);
	if (should_stop(philo->shared) == true)
	{
		pthread_mutex_unlock(&philo->shared->mutexes[PRINT]);
		return (0);
	}
	time = time_since(philo->shared->start_time);
	printf("%llu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->shared->mutexes[PRINT]);
	return (1);
}

int	ft_error(char *str, int ret)
{
	printf("%s\n", str);
	return (ret);
}
