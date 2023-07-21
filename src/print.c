/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 18:17:06 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/21 18:59:59 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colors.h"
#define COLOUR_COUNT 5

static void	print_colour(int id, bool should_print)
{
	char	*colors[COLOUR_COUNT] = {
		[0] = C_LYELLOW,
		[1] = C_LGREEN,
		[2] = C_RED,
		[3] = C_BLUE,
		[4] = C_LBLUE
	};

	if (should_print == true)
		printf("%s", colors[id % COLOUR_COUNT]);
}

int		print_update(t_philo *philo, char *str)
{
	t_llu		time;

	pthread_mutex_lock(&philo->shared->mutexes[PRINT]);
	if (should_stop(philo->shared) == true)
	{
		pthread_mutex_unlock(&philo->shared->mutexes[PRINT]);
		return (0);
	}
	time = time_since(philo->shared->start_time);
	print_colour(philo->id, false);
	printf("%llu %d %s%s\n", time, philo->id, str, C_RESET);

	pthread_mutex_unlock(&philo->shared->mutexes[PRINT]);
	return (1);
}

int	ft_error(void *data, char *str, int ret)
{
	if (data)
		free(data);

	printf("%s%s%s\n", C_RED, str, C_RESET);
	return (ret);
}
