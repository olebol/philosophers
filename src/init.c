/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 19:24:49 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/26 13:51:24 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <limits.h>

static int	ft_atoi_error(const char *str, int *result)
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
	if (tmp == 0)
		return (0);
	*result = tmp;
	return (1);
}

static void	assign_forks(t_philo *philos, t_mutex *forks, int amount)
{
	int		i;

	i = 0;
	while (i < amount)
	{
		philos[i].left_fork = &forks[i];
		if (i + 1 != amount)
			philos[i + 1].right_fork = &forks[i];
		i++;
	}
	philos[0].right_fork = &forks[i - 1];
}

static int	set_forks_and_mutexes(t_philo *philos, t_shared *shared)
{
	const int	all = shared->amount_of_philos;

	if (!init_eat_mutexes(philos, all))
	{
		destroy_mutex_array(shared->mutexes, SHARED_MUTEXES_SIZE);
		free(philos);
		return (0);
	}
	if (!init_last_eat_mutexes(philos, all))
	{
		destroy_mutex_array(shared->mutexes, SHARED_MUTEXES_SIZE);
		destroy_eat_mutexes(philos, all);
		free(philos);
		return (0);
	}
	if (!init_forks(shared, all))
	{
		destroy_mutex_array(shared->mutexes, SHARED_MUTEXES_SIZE);
		destroy_last_eat_mutexes(philos, all);
		destroy_eat_mutexes(philos, all);
		free(philos);
		return (0);
	}
	assign_forks(philos, shared->forks, all);
	return (1);
}

int	init_philos(t_philo **philo_ptr, t_shared *shared)
{
	t_philo		*philos;
	t_philo		*current;
	int			i;

	philos = (t_philo *) malloc(shared->amount_of_philos * sizeof(t_philo));
	if (!philos)
	{
		destroy_mutex_array(shared->mutexes, SHARED_MUTEXES_SIZE);
		return (0);
	}
	i = 0;
	while (i < shared->amount_of_philos)
	{
		current = &philos[i];
		current->id = i + 1;
		current->times_eaten = 0;
		current->time_last_eat = 0;
		current->shared = shared;
		i++;
	}
	if (!set_forks_and_mutexes(philos, shared))
		return (0);
	*philo_ptr = philos;
	return (1);
}

int	init_shared(t_shared *shared, int ac, char **av)
{
	shared->philos_created = 0;
	shared->should_stop = false;
	if (!ft_atoi_error(av[1], &shared->amount_of_philos)
		|| (!ft_atoi_error(av[2], &shared->death_time))
		|| (!ft_atoi_error(av[3], &shared->eat_time))
		|| (!ft_atoi_error(av[4], &shared->sleep_time))
		|| (ac == 6 && !ft_atoi_error(av[5], &shared->times_to_eat)))
		return (ft_error(INVALID_ARGS, 0));
	if (shared->amount_of_philos == 1)
	{
		printf("0 1 is thinking\n");
		printf("0 1 has taken a fork\n");
		printf("%d 1 died\n", shared->death_time + 1);
		return (0);
	}
	return (1);
}
