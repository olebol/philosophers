/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 22:57:22 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/20 21:54:37 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	create_threads(pthread_t *threads, t_philo *philos, int max_philos)
{
	int		i;

	i = 0;
	while (i < max_philos)
	{
		philos[i].time_last_eat = get_time();
		if (pthread_create(&threads[i], NULL, &routine, &philos[i]) != 0)
			return (0); // todo : join prev
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

int	start_threads(t_shared *shared, t_philo *philos)
{
	pthread_t	*threads;

	shared->start_time = get_time();
	threads = malloc(shared->number_of_philos * sizeof(pthread_t));
	if (!create_threads(threads, philos, shared->number_of_philos))
	{
		ft_error(NULL, "Error creating threads\n");
		return (0);
	}
	check_for_death_main_thread(shared, philos);
	join_threads(threads, shared->number_of_philos);
	return (1);
}
