/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 15:33:00 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/20 18:39:29 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_shared	shared;
	t_philo		*philos;
	t_mutex		*forks;

	if (ac != 5 && ac != 6)
		return (1);

	if (!init_shared(&shared, ac, av))
		return (2);

	if (!init_shared_mutexes(&shared))
		return (ft_error(NULL, MUTEX_INIT), 0);

	printf("input: %d %d %d %d %d\n\n", shared.number_of_philos, shared.death_time, shared.eat_time, shared.sleep_time, shared.times_to_eat);

	philos = init_philos(&shared);
	if (!philos)
		return (3);
	
	if (!init_eat_mutexes(philos, shared.number_of_philos))
		return (4); // todo: free philos

	forks = init_forks(shared.number_of_philos);
	if (!forks)
		return (5);
	assign_forks(philos, forks, shared.number_of_philos);

	if (start_threads(&shared, philos) == 0)
		return (6);

	// todo: destroy mutexes

	return (0);
}
