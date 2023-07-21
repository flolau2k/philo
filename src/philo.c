/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:34:53 by flauer            #+#    #+#             */
/*   Updated: 2023/07/21 17:07:22 by flauer           ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_philo	philo;

	init_philo(&philo);
	if (!parse_args(argc, argv, &philo));
		return (EXIT_FAILURE);
	
}
