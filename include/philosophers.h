/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 15:43:32 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/19 20:47:32 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <time.h>
# include <unistd.h> // write
# include <stdlib.h> // malloc and free
# include <stdio.h> // printf

# define INVALID_ARGS "Invalid arguments"
# define MUTEX_INIT "Mutex initialization failed"
# define MUTEX_LOCK "Mutex locking failed"
# define MUTEX_UNLOCK "Mutex unlocking failed"

# define TAKE_FORK	"has taken a fork"

#define LEFT 0
#define RIGHT 1

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
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	t_shared	*shared;
}	;

// init.c
t_shared	*init_shared(int ac, char **av);
t_philo		**init_philos(t_shared *shared);
t_mutex		*init_forks(int	number_of_forks);

// error.c
/** @brief Prints an error message to STDERR and frees the memory given as parameter data */
void		*ft_error(void *data, char *str);

// threads.c
int			start_threads(t_shared *shared, t_philo **philos);

// routine.c
void		*routine(void *data);

// utils.c
t_llu		get_time(void);
t_llu		time_since(t_llu start);
void		ft_sleep(int time_to_wait);

// forks.c
void		assign_forks(t_philo **philos, t_mutex *forks, int amount);

// print.c
int			print_update(t_philo *philo, char *str);

// eat.c
int			eat(t_philo *philo);

#endif