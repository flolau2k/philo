/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:34:53 by flauer            #+#    #+#             */
/*   Updated: 2023/07/25 18:06:04 by flauer           ###   ########.fr       */
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
	gettimeofday(&(table->start), NULL);
	table->pre_start_time = MS_WAIT_BEFORE_START;
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
	philo->eat_count = 0;
	philo->table = table;
	philo->last_eat = 0;
	philo->dead = false;
	if (id == table->num_p - 1)
	{
		philo->f2 = &table->forks[0];
		philo->f1 = &table->forks[id];
	}
	else
	{
		philo->f1 = &table->forks[id];
		philo->f2 = &table->forks[id + 1];
	}
}

bool	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_p);
	 //TODO: make sure to free properly in case of error!
	if (!table->forks)
		return (false);
	table->philos = malloc(sizeof(t_philo *) * table->num_p);
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

void	print_info(t_philo *philo, char *msg)
{
	if (philo->dead)
		return ;
	pthread_mutex_lock(&philo->table->out);
	printf("[%li]	%i %s\n",
		get_timestamp(&philo->table->pre_start_time), philo->id, msg);
	pthread_mutex_unlock(&philo->table->out);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->f1);
	print_info(philo, TAKE_FORK);
	pthread_mutex_lock(philo->f2);
	print_info(philo, TAKE_FORK);
	print_info(philo, EATING);
	philo->last_eat = get_timestamp(&philo->table->start);
	usleep(philo->table->tte * 1000);
	pthread_mutex_unlock(philo->f1);
	pthread_mutex_unlock(philo->f2);
}

void	sleep(t_philo *philo)
{
	print_info(philo, SLEEPING);
	usleep(philo->table->tts * 1000);
}

void	*ft_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (get_timestamp(&philo->table->start) < 0)
		usleep(100);
	while (true)
	{
		print_info(philo, THINKING);
		eat(philo);
		sleep(philo);
		if (philo->dead)
			return (NULL);
	}
}

void	check_dead(t_philo *philo)
{
	size_t	curr_time;

	curr_time = get_timestamp(&philo->table->start);
	if (curr_time - philo->last_eat > philo->table->ttd)
		philo->dead = true;
}

void	*waiter(void *param)
{
	t_table	*table;
	int		i;

	table = (t_table *)param;
	while (true)
	{
		i = 0;
		while (i < table->num_p)
		{
			check_dead(&table->philos[i]);
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_table		table;
	int			i;
	pthread_t	thread;

	i = 0;
	init_table(&table);
	if (!parse_args(argc, argv, &table) || !init_mutexes(&table))
		return (EXIT_FAILURE);
	while (i < table.num_p)
	{
		pthread_create(&table.philos[i].thread, NULL,
			&ft_philo, &table.philos[i]);
		i++;
	}
	pthread_create(&thread, NULL, &waiter, &table);
	return (0);
}
