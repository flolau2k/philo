/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:21:27 by flauer            #+#    #+#             */
/*   Updated: 2023/07/31 21:51:10 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_arg(char *arg)
{
	int	i;

	if (!arg)
		return (false);
	if (arg[0] != '+' && !ft_isdigit(arg[0]))
		return (false);
	i = 1;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		if (i > 11)
			return (false);
		++i;
	}
	return (true);
}

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
		pthread_create(&table.philos[i].thread, NULL, &ft_philo, &table.philos[i]);
		i++;
	}
	waiter(&table);
	i = -1;
	while (++i < table.num_p)
		pthread_join(table.philos[i].thread, NULL);
	free_table(&table);
	return (0);
}
