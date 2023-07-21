/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 15:33:00 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/21 16:54:44 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_shared	shared;
	t_philo		*philos;

	if (ac != 5 && ac != 6)
		return (ft_error(NULL, INVALID_ARGS, 1));
	if (!init_shared(&shared, ac, av))
		return (2);
	if (!init_shared_mutexes(&shared))
		return (3);
	if (!init_philos(&philos, &shared))
		return (4);
	if (!handle_threads(&shared, philos))
		return (5);
	cleanup(philos, &shared);
	return (0);
}
