/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:47:23 by flauer            #+#    #+#             */
/*   Updated: 2023/07/25 18:00:58 by flauer           ###   ########.fr       */
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

size_t	get_timestamp(t_timeval *start, size_t pre_start_time)
{
	t_timeval	curr_time;
	size_t		ret;

	gettimeofday(&curr_time, NULL);
	ret = get_milliseconds(&curr_time) - get_milliseconds(start);
	return (ret - pre_start_time);
}
