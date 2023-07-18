/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 15:43:32 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/18 20:01:32 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <time.h>
#include <unistd.h> // write
#include <stdlib.h> // malloc and free
#include <stdio.h> // printf
#define INVALID_ARGS 0

typedef pthread_mutex_t mutex_t;

typedef struct s_shared_data t_shared;

struct s_shared_data
{
	int			number_of_philos;
	int			death_time;
	int			eat_time;
	int			sleep_time;
	int			times_to_eat;
	mutex_t		mutexes;
	pthread_t	threads;
} ;

typedef struct s_philosopher t_philo;

struct s_philosopher
{
	time_t		time_since_eat;
	int			times_eaten;
	t_shared	*shared;
} ;

// init.c
t_shared	*init_shared(int ac, char **av);

// error.c
void		*ft_error(void	*data, int err);