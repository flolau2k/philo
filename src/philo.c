/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:34:53 by flauer            #+#    #+#             */
/*   Updated: 2023/07/24 16:39:56 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo)
{
	philo->num_p = 0;
	philo->ttd = 0;
	philo->tte = 0;
	philo->tts = 0;
	philo->eat_count = 0;
	gettimeofday(&(philo->start), NULL);
}

bool	parse_args(int argc, char **argv, t_philo *philo)
{
	if (argc < 5 || argc > 6)
		return (ft_err(ARGS_FAIL), false);
	philo->num_p = ft_atoi(argv[1]);
	philo->ttd = ft_atoi(argv[2]);
	philo->tte = ft_atoi(argv[3]);
	philo->tts = ft_atoi(argv[4]);
	if (argc == 6)
		philo->eat_count = ft_atoi(argv[5]);
	return (true);
}

bool	init_mutexes(t_philo *philo)
{
	int	i;

	i = 0;
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->num_p);
	if (!philo->forks)
		return (false);
	while (i < philo->num_p)
	{
		pthread_mutex_init(&(philo->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&philo->out, NULL);
	return (true);
}

void	print_info(t_philo *philo, int id, char *msg)
{
	pthread_mutex_lock(&philo->out);
	printf("[%li]	%i %s\n", get_timestamp(&philo->start), id, msg);
	pthread_mutex_unlock(&philo->out);
}

void	ft_philo(t_philo *philo, int id)
{
	int	thinktime;

	while (true)
	{
		print_info(philo, id, THINKING);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	int		i;

	i = 0;
	init_philo(&philo);
	if (!parse_args(argc, argv, &philo) || !init_mutexes(&philo))
		return (EXIT_FAILURE);
	while (i < philo.num_p)
	{
		pthread_create()
	}

	return (0);
}
