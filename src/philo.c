/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:34:53 by flauer            #+#    #+#             */
/*   Updated: 2023/08/01 10:51:31 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	single_fork(t_philo *philo)
{
	while (true)
	{
		if (get_mutex(&philo->table->stop))
			break ;
		usleep(1000);
	}
	return ;
}

void	grab_forks(t_philo *philo)
{
	if (philo->l_fork == philo->r_fork)
		single_fork(philo);
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_info(philo, TAKE_FORK);
		pthread_mutex_lock(philo->r_fork);
		print_info(philo, TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_info(philo, TAKE_FORK);
		pthread_mutex_lock(philo->l_fork);
		print_info(philo, TAKE_FORK);
	}
}

void	eat(t_philo *philo)
{
	grab_forks(philo);
	if (get_mutex(&philo->table->stop))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	print_info(philo, EATING);
	set_mutex(&philo->last_eat, get_timestamp(philo->table));
	philosleep(philo->table, philo->table->tte);
	increment_mutex(&philo->eat_count);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*ft_philo(void *param)
{
	t_philo	*philo;
	bool	first;

	philo = (t_philo *)param;
	first = true;
	while (true)
	{
		print_info(philo, THINKING);
		if (first && philo->id % 2 != 0)
		{
			first = false;
			philosleep(philo->table, philo->table->tte / 2);
		}
		eat(philo);
		print_info(philo, SLEEPING);
		philosleep(philo->table, philo->table->tts);
		if (get_mutex(&philo->table->stop))
			return (NULL);
	}
}
