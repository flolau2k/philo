/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:31:41 by flauer            #+#    #+#             */
/*   Updated: 2023/08/03 14:11:47 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table, int *num)
{
	int	i;

	i = 0;
	while (num && i < *num)
	{
		if (table->forks)
			pthread_mutex_destroy(&table->forks[i]);
		if (table->philos)
		{
			destroy_mutex(&table->philos[i].eat_count);
			destroy_mutex(&table->philos[i].last_eat);
		}
		i++;
	}
	destroy_mutex(&table->stop);
	free(table->philos);
	free(table->forks);
}
