/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:24:13 by flauer            #+#    #+#             */
/*   Updated: 2023/07/31 13:47:10 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_dead(t_philo *philo)
{
	ssize_t	curr_time;

	curr_time = get_timestamp(philo->table);
	if ((curr_time - get_mutex(&philo->last_eat)) > philo->table->ttd)
	{
		print_info(philo, DIED);
		return (true);
	}
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
			{
				set_mutex(&table->stop, true);
				return ;
			}
			i++;
		}
		philosleep(table, 1);
	}
}
