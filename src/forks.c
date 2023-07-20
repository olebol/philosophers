/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 17:11:26 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/20 18:30:47 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	assign_forks(t_philo *philos, t_mutex *forks, int amount)
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

	// for (int j = 0; j < amount; j++)
	// 	printf("philo %d\nleft: [%p] - [%p]\n\n", philos[j]->id, philos[j]->left_fork, philos[j]->right_fork);
}

