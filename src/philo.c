/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:34:53 by flauer            #+#    #+#             */
/*   Updated: 2023/07/28 14:25:05 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	single_fork(t_philo *philo)
{
	while (true)
	{
		pthread_mutex_lock(&philo->m_dead);
		if (philo->dead)
			break;
		pthread_mutex_unlock(&philo->m_dead);
		usleep(1000);
	}
	pthread_mutex_unlock(&philo->m_dead);
	return ;
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->f1);
	if (philo->dead)
	{
		pthread_mutex_unlock(philo->f1);
		return ;
	}
	print_info(philo, TAKE_FORK);
	if (philo->f1 == philo->f2)
		return (single_fork(philo));
	pthread_mutex_lock(philo->f2);
	if (philo->dead)
	{
		pthread_mutex_unlock(philo->f1);
		pthread_mutex_unlock(philo->f2);
		return ;
	}
	print_info(philo, TAKE_FORK);
	print_info(philo, EATING);
	philo->last_eat = get_timestamp(&philo->table->start, philo->table->pst);
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
	while (get_timestamp(&philo->table->start, philo->table->pst) < 0)
		usleep(100);
	while (true)
	{
		print_info(philo, THINKING);
		eat(philo);
		philosleep(philo);
		pthread_mutex_lock(&philo->m_dead);
		if (philo->dead)
			return (pthread_mutex_unlock(&philo->m_dead), NULL);
		if (philo->table->num_eat && philo->eat_count >= philo->table->num_eat)
		{
			print_info(philo, "left the table");
			philo->dead = true;
			return (pthread_mutex_unlock(&philo->m_dead), NULL);
		}
		pthread_mutex_unlock(&philo->m_dead);
	}
}

