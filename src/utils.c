/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 13:22:40 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/21 23:55:41 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <sys/time.h>

void	ft_sleep(int time_to_wait)
{
	t_llu	start;

	start = get_time();
	while ((get_time() - start) < (t_llu) time_to_wait)
		usleep(250);
}

t_llu	get_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

t_llu	time_since(t_llu start)
{
	return ((get_time() - start));
}

int	check_philo_amount(int philos, int time)
{
	if (philos == 0)
		return (ft_error(INVALID_ARGS, 0));
	if (philos == 1)
	{
		printf("0 1 is thinking\n");
		printf("0 1 has taken a fork\n");
		printf("%d has died\n", time +1);
		return (0);
	}
	return (1);
}
