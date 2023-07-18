/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 15:33:00 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/18 20:01:26 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_shared	*shared;

	if (ac != 5 && ac != 6)
		return (1);

	shared = init_shared(ac, av);
	if (!shared)
		return (2);

	printf("input: %d %d %d %d %d\n", shared->number_of_philos, shared->death_time, shared->eat_time, shared->sleep_time, shared->times_to_eat);

	return (0);
}