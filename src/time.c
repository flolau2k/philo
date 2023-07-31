/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:47:23 by flauer            #+#    #+#             */
/*   Updated: 2023/07/31 16:51:21 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_milliseconds()
{
	size_t		ret;
	t_timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	ret = curr_time.tv_sec * (1000000) + curr_time.tv_usec;
	ret /= 1000;
	return (ret);
}

ssize_t	get_timestamp(t_table *table)
{
	ssize_t		ret;

	ret = get_milliseconds() - table->tzero;
	return (ret);
	// return (ret - table->pst);
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
