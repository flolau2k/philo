/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:35:09 by flauer            #+#    #+#             */
/*   Updated: 2023/07/24 11:39:12 by flauer           ###   ########.fr       */
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

# define ARGS_FAIL "Received wrong count of Arguments"

typedef struct timeval t_timeval;

typedef struct s_philo
{
	int	num_p;
	int	ttd;
	int	tte;
	int	tts;
	int	eat_count;
}	t_philo;

// helpers.c
ssize_t		ft_atoi(const char *str);
void		ft_err(char *msg);

#endif