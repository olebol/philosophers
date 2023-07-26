/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 15:33:00 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/26 14:03:22 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_shared	shared;
	t_philo		*philos;

	if (ac != 5 && ac != 6)
		return (ft_error(INVALID_ARGS, 1));
	if (!init_shared(&shared, ac, av))
		return (2);
	if (!init_shared_mutexes(&shared))
		return (3);
	if (!init_philos(&philos, &shared))
		return (4);
	if (!handle_threads(&shared, philos))
		return (5);
	return (0);
}
