/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:34:53 by flauer            #+#    #+#             */
/*   Updated: 2023/07/28 16:10:39 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	single_fork(t_philo *philo)
{
	while (true)
	{
		if (get_mutex(&philo->table->stop))
			break;
		usleep(1000);
	}
	return ;
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->f1);
	if (get_mutex(&philo->table->stop))
	{
		pthread_mutex_unlock(philo->f1);
		return ;
	}
	print_info(philo, TAKE_FORK);
	if (philo->f1 == philo->f2)
		return (single_fork(philo));
	pthread_mutex_lock(philo->f2);
	if (get_mutex(&philo->table->stop))
	{
		pthread_mutex_unlock(philo->f1);
		pthread_mutex_unlock(philo->f2);
		return ;
	}
	print_info(philo, TAKE_FORK);
	print_info(philo, EATING);
	set_mutex(&philo->last_eat, \
		get_timestamp(&philo->table->tzero, philo->table->pst));
	increment_mutex(&philo->eat_count);
	usleep(philo->table->tte * 1000);
	pthread_mutex_unlock(philo->f1);
	pthread_mutex_unlock(philo->f2);
}

void	philosleep(t_philo *philo)
{
	print_info(philo, SLEEPING);
	usleep(philo->table->tts * 1000);
}

void	*ft_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (get_timestamp(&philo->table->tzero, philo->table->pst) < 0)
		usleep(100);
	while (true)
	{
		print_info(philo, THINKING);
		usleep(10);
		eat(philo);
		philosleep(philo);
		if (get_mutex(&philo->table->stop))
			return (NULL);
	}
}
