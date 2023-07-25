/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:35:09 by flauer            #+#    #+#             */
/*   Updated: 2023/07/25 18:08:05 by flauer           ###   ########.fr       */
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
# define DIED "died"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define TAKE_FORK "taken a fork"

typedef struct timeval t_timeval;

struct s_philo
{
	int				id;
	int				eat_count;
	t_table			*table;
	size_t			last_eat;
	bool			dead;
	pthread_mutex_t	*f1;
	pthread_mutex_t	*f2;
	pthread_t		thread;
};

typedef struct s_table
{
	int				num_p;
	int				ttd;
	int				tte;
	int				tts;
	int				num_eat;
	size_t			pre_start_time;
	t_timeval		start;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	out;
}	t_table;

typedef struct s_philo	t_philo;

// helpers.c
ssize_t		ft_atoi(const char *str);
void		ft_err(char *msg);

// time.c
size_t		get_timestamp(t_timeval *start);

#endif