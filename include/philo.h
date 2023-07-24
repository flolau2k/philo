/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:35:09 by flauer            #+#    #+#             */
/*   Updated: 2023/07/24 16:38:58 by flauer           ###   ########.fr       */
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

# define THINKING "is thinking"
# define DIED "died"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define TAKE_FORK "taken a fork"

typedef struct timeval t_timeval;

typedef struct s_philo
{
	int				num_p;
	int				ttd;
	int				tte;
	int				tts;
	int				eat_count;
	t_timeval		start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	out;
}	t_philo;

// helpers.c
ssize_t		ft_atoi(const char *str);
void		ft_err(char *msg);

// time.c
size_t		get_timestamp(t_timeval *start);

#endif