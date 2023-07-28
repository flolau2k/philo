/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:34:53 by flauer            #+#    #+#             */
/*   Updated: 2023/07/28 15:17:35 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	single_fork(t_philo *philo)
{
	while (true)
	{
		pthread_mutex_lock(&philo->table->m_stop);
		if (philo->table->stop)
			break;
		pthread_mutex_unlock(&philo->table->m_stop);
		usleep(1000);
	}
	pthread_mutex_unlock(&philo->table->m_stop);
	return ;
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->f1);
	if (philo->table->stop)
	{
		pthread_mutex_unlock(philo->f1);
		return ;
	}
	print_info(philo, TAKE_FORK);
	if (philo->f1 == philo->f2)
		return (single_fork(philo));
	pthread_mutex_lock(philo->f2);
	if (philo->table->stop)
	{
		pthread_mutex_unlock(philo->f1);
		pthread_mutex_unlock(philo->f2);
		return ;
	}
	print_info(philo, TAKE_FORK);
	print_info(philo, EATING);
	philo->last_eat = get_timestamp(&philo->table->tzero, philo->table->pst);
	philo->eat_count += 1;
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
		eat(philo);
		philosleep(philo);
		pthread_mutex_lock(&philo->table->m_stop);
		if (philo->table->stop)
			return (pthread_mutex_unlock(&philo->table->m_stop), NULL);
		pthread_mutex_unlock(&philo->table->m_stop);
	}
}
