/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:08:32 by flauer            #+#    #+#             */
/*   Updated: 2023/07/28 15:47:55 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_mutex *m)
{
	m->val = 0;
	pthread_mutex_init(&m->mutex, NULL);
}

void	destroy_mutex(t_mutex *m)
{
	pthread_mutex_destroy(&m->mutex);
}

ssize_t		get_mutex(t_mutex *m)
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
