/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 19:24:49 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/20 21:41:14 by opelser       ########   odam.nl         */
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

int	init_shared(t_shared *shared, int ac, char **av)
{
	if (!ft_err_atoi(av[1], &shared->number_of_philos))
		return (ft_error(shared, INVALID_ARGS), 0);
	if (!ft_err_atoi(av[2], &shared->death_time))
		return (ft_error(shared, INVALID_ARGS), 0);
	if (!ft_err_atoi(av[3], &shared->eat_time))
		return (ft_error(shared, INVALID_ARGS), 0);
	if (!ft_err_atoi(av[4], &shared->sleep_time))
		return (ft_error(shared, INVALID_ARGS), 0);
	if (ac == 6 && !ft_err_atoi(av[5], &shared->times_to_eat))
		return (ft_error(shared, INVALID_ARGS), 0);
	else if (ac != 6)
		shared->times_to_eat = 0;
	shared->start_time = 0;

	return (1);
}

t_philo	*init_philos(t_shared *shared)
{
	t_philo		*philos;
	t_philo		*current;
	int			i;

	philos = (t_philo *) malloc(shared->number_of_philos * sizeof(t_philo));
	if (!philos)
		return (NULL);
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
	return (philos);
}

