/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 19:24:49 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/19 17:13:02 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <limits.h> // MAX and MIN INT

static int	ft_err_atoi(const char *str, int *result)
{
	int		i;
	long	tmp;

	tmp = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		tmp = tmp * 10 + (str[i] - '0');
		if (tmp > INT_MAX)
			return (0);
		i++;
	}
	*result = tmp;
	return (1);
}

t_mutex	*init_mutexes(void)
{
	static t_mutex		mutexes[1];

	if (pthread_mutex_init(&mutexes[PRINT_MUTEX], NULL) != 0)
		return (NULL);
	// todo: destroy all mutexes on fail
	return (mutexes);
}

t_shared	*init_shared(int ac, char **av)
{
	t_shared	*shared;

	shared = (t_shared *) malloc(sizeof(t_shared));
	if (!shared)
		return (NULL);

	if (!ft_err_atoi(av[1], &shared->number_of_philos))
		return (ft_error(shared, INVALID_ARGS));
	if (!ft_err_atoi(av[2], &shared->death_time))
		return (ft_error(shared, INVALID_ARGS));
	if (!ft_err_atoi(av[3], &shared->eat_time))
		return (ft_error(shared, INVALID_ARGS));
	if (!ft_err_atoi(av[4], &shared->sleep_time))
		return (ft_error(shared, INVALID_ARGS));
	if (ac == 6 && !ft_err_atoi(av[5], &shared->times_to_eat))
		return (ft_error(shared, INVALID_ARGS));
	else if (ac != 6)
		shared->times_to_eat = 0;
	shared->start_time = 0;
	shared->mutexes = init_mutexes();
	if (!shared->mutexes)
		return (ft_error(NULL, MUTEX_INIT));

	return (shared);
}

t_philo	**init_philos(t_shared *shared)
{
	t_philo		**philos;
	t_philo		*current;
	int			i;

	philos = (t_philo **) malloc(shared->number_of_philos * sizeof(t_philo *));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < shared->number_of_philos)
	{
		current = (t_philo *) malloc(sizeof(t_philo));
		if (!current)
			return (NULL); // todo: free all philos var + individual philos
		current->id = i + 1;
		current->times_eaten = 0;
		current->time_since_eat = 0;
		current->shared = shared;
		philos[i] = current;
		i++;
	}
	return (philos);
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
			return (ft_error(NULL, MUTEX_INIT)); // todo: destroy all mutexes
		i++;
	}
	return (forks);
}
