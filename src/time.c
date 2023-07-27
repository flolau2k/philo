/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:47:23 by flauer            #+#    #+#             */
/*   Updated: 2023/07/27 10:01:45 by flauer           ###   ########.fr       */
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

ssize_t	get_timestamp(t_timeval *start, size_t pst)
{
	t_timeval	curr_time;
	ssize_t		ret;

	gettimeofday(&curr_time, NULL);
	ret = get_milliseconds(&curr_time) - get_milliseconds(start);
	return (ret - pst);
}
