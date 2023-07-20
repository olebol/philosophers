/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 18:17:06 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/20 21:35:42 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colors.h"
#define COLOUR_COUNT 5

static void	print_colour(int id)
{
	char	*colors[COLOUR_COUNT] = {
		[0] = C_YELLOW,
		[1] = C_GREEN,
		[2] = C_RED,
		[3] = C_BLUE,
		[4] = C_LBLUE
	};
	printf("%s", colors[id % COLOUR_COUNT]);
}

int		print_update(t_philo *philo, char *str)
{
	t_llu		time;

	time = time_since(philo->shared->start_time);
	pthread_mutex_lock(&philo->shared->mutexes[PRINT]);
	if (should_stop(philo->shared) == true)
	{
		pthread_mutex_unlock(&philo->shared->mutexes[PRINT]);
		return (0);
	}
	print_colour(philo->id);
	printf("%llu %d %s%s\n", time, philo->id, str, C_RESET);

	pthread_mutex_unlock(&philo->shared->mutexes[PRINT]);
	return (1);
}
