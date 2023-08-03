/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:21:27 by flauer            #+#    #+#             */
/*   Updated: 2023/08/03 12:24:45 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table		table;
	int			i;

	i = 0;
	init_table(&table);
	if (!parse_args(argc, argv, &table) || !init_philos(&table))
		return (EXIT_FAILURE);
	table.tzero = get_milliseconds();
	while (i < table.num_p)
	{
		if (pthread_create(&table.philos[i].thread, NULL, \
			&ft_philo, &table.philos[i]))
			return (ft_err(&table, PTHREAD_ERR), EXIT_FAILURE); //TODO detatch all previous and free table
		i++;
	}
	waiter(&table);
	i = -1;
	while (++i < table.num_p)
		pthread_join(table.philos[i].thread, NULL);
	free_table(&table);
	return (0);
}
