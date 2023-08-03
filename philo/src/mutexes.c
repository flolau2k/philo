/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:08:32 by flauer            #+#    #+#             */
/*   Updated: 2023/08/03 14:15:11 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_mutex(t_mutex *m)
{
	m->val = 0;
	if (pthread_mutex_init(&m->mutex, NULL))
		return (false);
	return (true);
}

bool	destroy_mutex(t_mutex *m)
{
	if (pthread_mutex_destroy(&m->mutex))
		return (false);
	return (true);
}

ssize_t	get_mutex(t_mutex *m)
{
	ssize_t	ret;

	ret = 0;
	pthread_mutex_lock(&m->mutex);
	ret = m->val;
	pthread_mutex_unlock(&m->mutex);
	return (ret);
}

void	set_mutex(t_mutex *m, ssize_t newval)
{
	pthread_mutex_lock(&m->mutex);
	m->val = newval;
	pthread_mutex_unlock(&m->mutex);
}

ssize_t	increment_mutex(t_mutex *m)
{
	ssize_t	ret;

	ret = 0;
	pthread_mutex_lock(&m->mutex);
	(m->val)++;
	ret = m->val;
	pthread_mutex_unlock(&m->mutex);
	return (ret);
}
