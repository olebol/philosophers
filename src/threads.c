/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 22:57:22 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/25 21:45:49 by opelser       ########   odam.nl         */
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

static int	create_threads(pthread_t *threads, t_philo *philos,
	t_shared *shared)
{
	int			i;

	i = 0;
	pthread_mutex_lock(&shared->mutexes[SHOULD_START]);
	while (i < shared->number_of_philos)
	{
		if (pthread_create(&threads[i], NULL, &routine, &philos[i]) != 0)
		{
			pthread_mutex_unlock(&shared->mutexes[SHOULD_START]);
			join_previous_threads(threads, i);
			return (0);
		}
		shared->philos_created++;
		i++;
	}
	shared->start_time = get_time();
	pthread_mutex_unlock(&shared->mutexes[SHOULD_START]);
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
	int			ret;

	threads = malloc(shared->number_of_philos * sizeof(pthread_t));
	if (!threads)
	{
		cleanup(philos, shared);
		return (ft_error("Threads malloc error", 0));
	}
	if (!create_threads(threads, philos, shared))
	{
		cleanup(philos, shared);
		return (ft_error("Error creating threads", 0));
	}
	ret = monitor(shared, philos);
	join_threads(threads, shared->number_of_philos);
	if (!ret)
		cleanup(philos, shared);
	return (ret);
}
