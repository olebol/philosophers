/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 18:17:06 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/19 18:17:59 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colors.h"

static void	print_colour(int id)
{
	char	*colors[5] = {
		[0] = C_YELLOW,
		[1] = C_GREEN,
		[2] = C_RED,
		[3] = C_BLUE,
		[4] = C_LBLUE
	};
	if (id == 0)
		printf("%s", C_RESET);
	else
		printf("%s", colors[id - 1]);
}

int		print_update(t_philo *philo, char *str)
{
	if (pthread_mutex_lock(&philo->shared->mutexes[PRINT_MUTEX]) != 0)
	{
		ft_error(NULL, MUTEX_LOCK);
		return (0);
	}

	print_colour(philo->id);
	printf("%llu ", time_since(philo->shared->start_time));
	printf("%d ", philo->id);
	printf("%s\n", str);
	print_colour(0);

	if (pthread_mutex_unlock(&philo->shared->mutexes[PRINT_MUTEX]) != 0)
	{
		ft_error(NULL, MUTEX_UNLOCK);
		return (0);
	}
	return (1);
}
