/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 15:38:50 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/19 22:57:55 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_loop(t_philo *philo)
{
	if (!eat(philo))
		return (0);

	print_update(philo, "is sleeping");
	ft_sleep(philo->shared->sleep_time);
	return (1);
}

void	*routine(void *data)
{
	t_philo		*philo;

	philo = (t_philo *) data;
	while (philo->times_eaten < philo->shared->times_to_eat) // todo: this stops them from eating, even if not all of them have finished all their meals yet
	{
		if (!philo_loop(philo))
			return (NULL);
	}
	return ("SUCCES");
}
