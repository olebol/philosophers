/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 22:57:22 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/21 19:54:58 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	join_previous_threads(pthread_t *threads, int amount)
{
	int		i;

	i = 0;
	while (i < amount)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

static int	create_threads(pthread_t *threads, t_philo *philos, int max_philos)
{
	int		i;

	i = 0;
	while (i < max_philos)
	{
		philos[i].time_last_eat = get_time();
		if (pthread_create(&threads[i], NULL, &routine, &philos[i]) != 0)
		{
			join_previous_threads(threads, i);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	join_threads(pthread_t *threads, int max_philos)
{
	int		i;

	i = 0;
	while (i < max_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	handle_threads(t_shared *shared, t_philo *philos)
{
	pthread_t	*threads;

	shared->start_time = get_time();
	threads = malloc(shared->number_of_philos * sizeof(pthread_t));
	if (!create_threads(threads, philos, shared->number_of_philos))
	{
		ft_error("Error creating threads\n", 0);
		cleanup(philos, shared);
		return (0);
	}
	monitor(shared, philos);
	join_threads(threads, shared->number_of_philos);
	return (1);
}
