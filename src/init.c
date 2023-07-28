/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:20:00 by flauer            #+#    #+#             */
/*   Updated: 2023/07/28 16:46:25 by flauer           ###   ########.fr       */
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
	gettimeofday(&(table->tzero), NULL);
	table->pst = MS_WAIT_BEFORE_START;
	table->philos = NULL;
	table->forks = NULL;
}

bool	parse_args(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
		return (ft_err(ARGS_FAIL), false);
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
	philo->id = id;
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
	//TODO: make sure to free properly in case of error!
	if (!table->forks)
		return (false);
	table->philos = malloc(sizeof(t_philo) * table->num_p);
	if (!table->philos)
		return (false);
	while (i < table->num_p)
	{
		pthread_mutex_init(&(table->forks[i]), NULL);
		create_philo(&table->philos[i], i, table);
		i++;
	}
	pthread_mutex_init(&table->out, NULL);
	return (true);
}
