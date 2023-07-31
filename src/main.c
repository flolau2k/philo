/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:21:27 by flauer            #+#    #+#             */
/*   Updated: 2023/07/31 12:42:47 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table		table;
	int			i;
	pthread_t	thread;

	i = 0;
	init_table(&table);
	if (!parse_args(argc, argv, &table) || !init_philos(&table))
		return (EXIT_FAILURE);
	while (i < table.num_p)
	{
		pthread_create(&table.philos[i].thread, NULL,
			&ft_philo, &table.philos[i]);
		i++;
	}
	pthread_create(&thread, NULL, &waiter, &table);
	i = -1;
	while (i++ < table.num_p)
		pthread_join(table.philos[i].thread, NULL);
	pthread_join(thread, NULL);
	return (0);
}
