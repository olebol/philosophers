/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 15:38:50 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/20 23:12:00 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
