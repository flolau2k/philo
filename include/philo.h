/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:35:09 by flauer            #+#    #+#             */
/*   Updated: 2023/07/28 11:42:43 by flauer           ###   ########.fr       */
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
# define MS_WAIT_BEFORE_START 100

# define THINKING "is thinking"
# define DIED "\033[0;31mdied\033[0m"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define TAKE_FORK "has taken a fork"

typedef struct timeval t_timeval;

typedef struct s_philo t_philo;
typedef struct s_table t_table;

struct s_philo
{
	int				id;
	int				eat_count;
	t_table			*table;
	ssize_t			last_eat;
	bool			dead;
	pthread_mutex_t	dead_m;
	pthread_mutex_t	*f1;
	pthread_mutex_t	*f2;
	pthread_t		thread;
};

struct s_table
{
	int				num_p;
	int				ttd;
	int				tte;
	int				tts;
	int				num_eat;
	ssize_t			pst;
	t_timeval		start;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	out;
};

// helpers.c
ssize_t		ft_atoi(const char *str);
void		ft_err(char *msg);

// time.c
ssize_t		get_timestamp(t_timeval *start, size_t pst);

#endif