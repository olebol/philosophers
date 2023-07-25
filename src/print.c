/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 18:17:06 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/25 18:45:41 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colors.h"
#define COLOUR_COUNT 5

static void	print_colour(int id)
{
	const char	*colors[COLOUR_COUNT] = {
	[0] = C_LYELLOW,
	[1] = C_LGREEN,
	[2] = C_RED,
	[3] = C_BLUE,
	[4] = C_LBLUE
	};

	printf("%s", colors[id % COLOUR_COUNT]);
}

int	print_update(t_philo *philo, char *str)
{
	t_llu		time;

	if (pthread_mutex_lock(&philo->shared->mutexes[PRINT]) != 0)
		printf("FUCK\n");
	time = time_since(philo->shared->start_time);
	if (should_stop(philo->shared) == true)
	{
		pthread_mutex_unlock(&philo->shared->mutexes[PRINT]);
		return (0);
	}
	if (COLOUR_ON)
		print_colour(philo->id);
	printf("%llu %d %s\n", time, philo->id, str);
	if (COLOUR_ON)
		printf("%s", C_RESET);
	pthread_mutex_unlock(&philo->shared->mutexes[PRINT]);
	return (1);
}

int	ft_error(char *str, int ret)
{
	printf("%s%s%s\n", C_RED, str, C_RESET);
	return (ret);
}
