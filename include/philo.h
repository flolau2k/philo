/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:35:09 by flauer            #+#    #+#             */
/*   Updated: 2023/07/31 16:51:10 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

# define ARGS_FAIL "Received wrong number of Arguments"
// # define MS_WAIT_BEFORE_START 100
# define BUSY_WAIT_SLEEP 100

# define THINKING "is thinking"
//# define DIED "\033[0;31mdied\033[0m"
# define DIED "died"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define TAKE_FORK "has taken a fork"

typedef struct timeval t_timeval;

typedef struct s_mutex
{
	ssize_t			val;
	pthread_mutex_t	mutex;
}	t_mutex;

typedef struct s_philo t_philo;
typedef struct s_table t_table;

struct s_philo
{
	int				id;
	t_table			*table;
	t_mutex			eat_count;
	t_mutex			last_eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		thread;
};

struct s_table
{
	int				num_p;
	int				ttd;
	int				tte;
	int				tts;
	int				num_eat;
	// int				pst;
	t_mutex			stop;
	size_t			tzero;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	out;
};

// main.c
int			main(int argc, char **argv);

// init.c
void		init_table(t_table *table);
bool		parse_args(int argc, char **argv, t_table *table);
void		create_philo(t_philo *philo, int id, t_table *table);
bool		init_philos(t_table *table);

// waiter.c
bool		check_dead(t_philo *philo);
void		set_all_philos_dead(t_table *table);
void		waiter(t_table *table);

//philo.c
void		*ft_philo(void *param);
void		eat(t_philo *philo);
void		single_fork(t_philo *philo);
void		grab_forks(t_philo *philo);

// helpers.c
ssize_t		ft_atoi(const char *str);
void		ft_err(char *msg);
void		print_info(t_philo *philo, char *msg);

// mutexes.c
void		init_mutex(t_mutex *m);
void		destroy_mutex(t_mutex *m);
ssize_t		get_mutex(t_mutex *m);
void		set_mutex(t_mutex *m, ssize_t newval);
ssize_t		increment_mutex(t_mutex *m);

// time.c
ssize_t		get_timestamp(t_table *table);
size_t		get_milliseconds();
void		philosleep(t_table *table, ssize_t wait_for);

#endif