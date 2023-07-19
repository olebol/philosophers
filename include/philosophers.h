/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 15:43:32 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/19 16:36:24 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <time.h>
# include <unistd.h> // write
# include <stdlib.h> // malloc and free
# include <stdio.h> // printf

# define INVALID_ARGS 0
# define MUTEX_INIT 1

#define PRINT_MUTEX 0

typedef unsigned long long		t_llu;

typedef pthread_mutex_t			t_mutex;

typedef struct s_shared_data	t_shared;

struct s_shared_data
{
	int			number_of_philos;
	int			death_time;
	int			eat_time;
	int			sleep_time;
	int			times_to_eat;
	t_llu		start_time;
	t_mutex		*mutexes;
}	;

typedef struct s_philosopher	t_philo;

struct s_philosopher
{
	int			id;
	time_t		time_since_eat;
	int			times_eaten;
	t_shared	*shared;
}	;

// init.c
t_shared	*init_shared(int ac, char **av);
t_philo		**init_philos(t_shared *shared);

// error.c
/** @brief Prints an error message to STDERR and frees the memory given as parameter data */
void		*ft_error(void	*data, int err);

// threads.c
int			start_threads(t_shared *shared, t_philo **philos);

// routine.c
void		*routine(void *data);

// utils.c
t_llu		get_time(void);
t_llu		time_since(t_llu start);

#endif