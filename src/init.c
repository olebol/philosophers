/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 19:24:49 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/21 23:52:44 by opelser       ########   odam.nl         */
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
	t_mutex		*forks;
	const int	amount = shared->number_of_philos;

	if (!init_eat_mutexes(philos, amount))
	{
		destroy_mutex_array(shared->mutexes, SHARED_MUTEXES_SIZE);
		free(philos);
		return (0);
	}
	if (!init_last_eat_mutexes(philos, amount))
	{
		destroy_mutex_array(shared->mutexes, SHARED_MUTEXES_SIZE);
		destroy_eat_mutexes(philos, amount);
		free(philos);
		return (0);
	}
	if (!init_forks(&forks, amount))
	{
		destroy_mutex_array(shared->mutexes, SHARED_MUTEXES_SIZE);
		destroy_eat_mutexes(philos, amount);
		free(philos);
		return (0);
	}
	assign_forks(philos, forks, amount);
	return (1);
}

int	init_philos(t_philo **philo_ptr, t_shared *shared)
{
	t_philo		*philos;
	t_philo		*current;
	int			i;

	philos = (t_philo *) malloc(shared->number_of_philos * sizeof(t_philo));
	if (!philos)
	{
		destroy_mutex_array(shared->mutexes, SHARED_MUTEXES_SIZE);
		return (0);
	}
	i = 0;
	while (i < shared->number_of_philos)
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
	shared->times_to_eat = 0;
	shared->start_time = 0;
	shared->philos_created = 0;
	if (!ft_atoi_error(av[1], &shared->number_of_philos)
		|| (!ft_atoi_error(av[2], &shared->death_time))
		|| (!ft_atoi_error(av[3], &shared->eat_time))
		|| (!ft_atoi_error(av[4], &shared->sleep_time))
		|| (ac == 6 && !ft_atoi_error(av[5], &shared->times_to_eat)))
		return (ft_error(INVALID_ARGS, 0));
	if (!check_philo_amount(shared->number_of_philos, shared->death_time))
		return (0);
	return (1);
}
