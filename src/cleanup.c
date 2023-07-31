/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:31:41 by flauer            #+#    #+#             */
/*   Updated: 2023/07/31 21:41:15 by flauer           ###   ########.fr       */
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
		i++;
	}
	free(table->philos);
	free(table->forks);
}
