/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:24:13 by flauer            #+#    #+#             */
/*   Updated: 2023/08/01 12:15:26 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_dead(t_philo *philo)
{
	ssize_t	curr_time;

	curr_time = get_timestamp(philo->table);
	pthread_mutex_lock(&philo->last_eat.mutex);
	if ((curr_time - philo->last_eat.val) > philo->table->ttd)
	{
		pthread_mutex_lock(&philo->table->stop.mutex);
		printf("%li %i %s\n", get_timestamp(philo->table), philo->id, DIED);
		philo->table->stop.val = true;
		pthread_mutex_unlock(&philo->table->stop.mutex);
		pthread_mutex_unlock(&philo->last_eat.mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->last_eat.mutex);
	return (false);
}

bool	check_enough_eaten(t_table *table)
{
	int	i;

	i = 0;
	if (table->num_eat == 0)
		return (false);
	while (i < table->num_p)
	{
		if (get_mutex(&table->philos[i].eat_count) < table->num_eat)
			return (false);
		i++;
	}
	set_mutex(&table->stop, true);
	return (true);
}

void	waiter(t_table	*table)
{
	int		i;

	while (true)
	{
		i = 0;
		while (i < table->num_p)
		{
			if (check_dead(&table->philos[i]) || check_enough_eaten(table))
				return ;
			i++;
		}
		philosleep(table, 1);
	}
}
