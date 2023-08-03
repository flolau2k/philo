/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:20:00 by flauer            #+#    #+#             */
/*   Updated: 2023/08/03 14:26:46 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table)
{
	table->num_p = 0;
	table->ttd = 0;
	table->tte = 0;
	table->tts = 0;
	table->num_eat = 0;
	init_mutex(&table->stop);
	table->tzero = 0;
	table->philos = NULL;
	table->forks = NULL;
}

bool	check_arg(char *arg)
{
	int		i;
	ssize_t	val;

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
	val = ft_atoi(arg);
	if (val > INT_MAX || val <= 0)
		return (false);
	return (true);
}

bool	parse_args(int argc, char **argv, t_table *table)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (ft_err(table, ARGS_COUNT), false);
	while (++i < argc)
	{
		if (!check_arg(argv[i]))
			return (ft_err(table, ARGS_FAIL), false);
	}
	table->num_p = ft_atoi(argv[1]);
	table->ttd = ft_atoi(argv[2]);
	table->tte = ft_atoi(argv[3]);
	table->tts = ft_atoi(argv[4]);
	if (argc == 6)
		table->num_eat = ft_atoi(argv[5]);
	return (true);
}

void	create_philo(t_philo *philo, int id, t_table *table)
{
	philo->id = id + 1;
	philo->table = table;
	init_mutex(&philo->eat_count);
	init_mutex(&philo->last_eat);
	philo->l_fork = &table->forks[id];
	if (id == table->num_p - 1)
		philo->r_fork = &table->forks[0];
	else
		philo->r_fork = &table->forks[id + 1];
}

bool	init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_p);
	if (!table->forks)
		return (ft_err(table, MALLOC_ERR), false);
	table->philos = malloc(sizeof(t_philo) * table->num_p);
	if (!table->philos)
		return (ft_err(table, MALLOC_ERR), false);
	while (i < table->num_p)
	{
		pthread_mutex_init(&(table->forks[i]), NULL);
		create_philo(&table->philos[i], i, table);
		i++;
	}
	return (true);
}
