/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 22:57:22 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/19 14:19:55 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	*routine(void *data) // move this function?
{
	t_philo		*philo;

	philo = (t_philo *) data;
	printf("%llu\t", time_since(philo->shared->start_time));
	printf("Hello world from philo %d\n", philo->id);
	return (NULL);
}

static int	create_threads(pthread_t *threads, t_philo **philos, int max_philos)
{
	int		i;

	i = 0;
	while (i < max_philos)
	{
		if (pthread_create(&threads[i], NULL, &routine, philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

static int	join_threads(pthread_t *threads, int max_philos)
{
	int		i;

	i = 0;
	while (i < max_philos)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	start_threads(t_shared *shared, t_philo **philos)
{
	pthread_t	*threads;

	shared->start_time = get_time();
	threads = malloc(shared->number_of_philos * sizeof(pthread_t));
	if (!create_threads(threads, philos, shared->number_of_philos))
	{
		perror("Error creating threads\n");
		return (0);
	}
	if (!join_threads(threads, shared->number_of_philos))
	{
		perror("Error joining threads\n");
		return (0);
	}
	return (1);
}
