/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 15:43:32 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/26 14:29:20 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

typedef enum e_shared_mutexes {
	PRINT,
	SHOULD_START,
	SHOULD_STOP,
	SHARED_MUTEXES_SIZE
}	t_shared_mutexes;

typedef unsigned long long		t_llu;
typedef pthread_mutex_t			t_mutex;

typedef struct s_shared_data	t_shared;

struct s_shared_data
{
	int			amount_of_philos;
	int			philos_created;

	int			death_time;
	int			eat_time;
	int			sleep_time;
	int			times_to_eat;

	t_llu		start_time;

	bool		should_stop;

	t_mutex		*forks;
	t_mutex		mutexes[SHARED_MUTEXES_SIZE];
}	;

typedef struct s_philosopher	t_philo;

struct s_philosopher
{
	int			id;

	int			times_eaten;
	t_mutex		eat_mutex;

	t_llu		time_last_eat;
	t_mutex		last_eat_mutex;

	t_mutex		*left_fork;
	t_mutex		*right_fork;
	t_shared	*shared;
}	;

// init.c
int			init_shared(t_shared *shared, int ac, char **av);
int			init_philos(t_philo **philo_ptr, t_shared *shared);

// init_mutexes.c
int			init_last_eat_mutexes(t_philo *philos, int amount);
int			init_eat_mutexes(t_philo *philos, int amount);
int			init_shared_mutexes(t_shared *shared);
int			init_forks(t_shared *shared, int number_of_forks);

// threads.c
int			handle_threads(t_shared *shared, t_philo *philos);

// routine.c
void		*routine(void *data);

// monitor.c
int			monitor(t_shared *shared, t_philo *philos);

// utils.c
t_llu		get_time(void);
t_llu		time_since(t_llu start);
void		ft_sleep(int time_to_wait);
bool		should_stop(t_shared *shared);

// print.c
int			print_update(t_philo *philo, char *str);
int			ft_error(char *str, int ret);

// cleanup.c
void		destroy_last_eat_mutexes(t_philo *philos, int amount);
void		destroy_eat_mutexes(t_philo *philos, int amount);
void		destroy_mutex_array(t_mutex *mutexes, int amount);
void		cleanup(t_philo *philos, t_shared *shared);

#endif
