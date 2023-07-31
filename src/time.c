/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:47:23 by flauer            #+#    #+#             */
/*   Updated: 2023/07/31 12:52:41 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	get_milliseconds(t_timeval *val)
{
	size_t	ret;

	ret = val->tv_sec * (1000000) + val->tv_usec;
	ret /= 1000;
	return (ret);
}

ssize_t	get_timestamp(t_table *table)
{
	t_timeval	curr_time;
	ssize_t		ret;

	gettimeofday(&curr_time, NULL);
	ret = get_milliseconds(&curr_time) - get_milliseconds(&table->tzero);
	// return (ret);
	return (ret - table->pst);
}

void	philosleep(t_table *table, ssize_t wait_for)
{
	ssize_t	start;
	ssize_t	timestamp;

	start = get_timestamp(table);
	timestamp = get_timestamp(table);
	while (timestamp < start + wait_for)
	{
		usleep(BUSY_WAIT_SLEEP);
		timestamp = get_timestamp(table);
	}
	return ;
}
