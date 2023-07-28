/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:24:13 by flauer            #+#    #+#             */
/*   Updated: 2023/07/28 14:24:57 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_dead(t_philo *philo)
{
	ssize_t	curr_time;

	curr_time = get_timestamp(&philo->table->start, philo->table->pst);
	// printf("time since last eat is %li, ttd is %i\n", (curr_time - philo->last_eat), philo->table->ttd);
	if ((curr_time - philo->last_eat) > philo->table->ttd)
	{
		print_info(philo, DIED);
		pthread_mutex_lock(&philo->m_dead);
		philo->dead = true;
		pthread_mutex_unlock(&philo->m_dead);
		return (true);
	}
	return (false);
}

void	set_all_philos_dead(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_p)
	{
		pthread_mutex_lock(&table->philos[i].m_dead);
		table->philos[i].dead = true;
		pthread_mutex_unlock(&table->philos[i].m_dead);
		i++;
	}
}

void	*waiter(void *param)
{
	t_table	*table;
	int		i;
	bool	one_dead;

	table = (t_table *)param;
	one_dead = false;
	while (!one_dead)
	{
		i = 0;
		while (i < table->num_p)
		{
			if (table->philos[i].dead || check_dead(&table->philos[i]))
			{
				one_dead = true;
				break;
			}
			i++;
		}
		if (one_dead)
			set_all_philos_dead(table);
		usleep(1000);
	}
	return (NULL);
}
