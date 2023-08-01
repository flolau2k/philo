/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:31:41 by flauer            #+#    #+#             */
/*   Updated: 2023/08/01 11:43:52 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_p)
	{
		pthread_mutex_destroy(&table->forks[i]);
		destroy_mutex(&table->philos[i].eat_count);
		destroy_mutex(&table->philos[i].last_eat);
		i++;
	}
	destroy_mutex(&table->stop);
	free(table->philos);
	free(table->forks);
}
