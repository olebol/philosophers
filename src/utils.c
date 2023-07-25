/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 13:22:40 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/25 23:32:24 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <sys/time.h>

void	ft_sleep(int time_to_wait)
{
	t_llu	start;

	start = get_time();
	usleep((time_to_wait / 2) * 1000);
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

bool	should_stop(t_shared *shared)
{
	bool	ret;

	pthread_mutex_lock(&shared->mutexes[SHOULD_STOP]);
	ret = shared->should_stop;
	pthread_mutex_unlock(&shared->mutexes[SHOULD_STOP]);
	return (ret);
}
