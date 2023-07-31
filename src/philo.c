/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:34:53 by flauer            #+#    #+#             */
/*   Updated: 2023/07/31 08:32:23 by flauer           ###   ########.fr       */
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
	print_info(philo, EATING);
	set_mutex(&philo->last_eat, \
		get_timestamp(&philo->table->tzero, philo->table->pst));
	usleep(philo->table->tte * 1000);
	increment_mutex(&philo->eat_count);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philosleep(t_philo *philo)
{
	print_info(philo, SLEEPING);
	usleep(philo->table->tts * 1000);
}

ssize_t	get_thinktime(t_philo *philo)
{
	ssize_t	time_since_last_eat;
	ssize_t	time_to_spare;
	ssize_t	curr_time;

	curr_time = get_timestamp(&philo->table->tzero, philo->table->pst);
	time_since_last_eat = curr_time - get_mutex(&philo->last_eat);
	time_to_spare = philo->table->ttd - philo->table->tte - philo->table->tts;
	if (time_since_last_eat <= philo->table->tts + philo->table->tte + 10)
		return (time_to_spare / 32);
	return (0);
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
		usleep(get_thinktime(philo) * 1000);
		eat(philo);
		philosleep(philo);
		if (get_mutex(&philo->table->stop))
			return (NULL);
	}
}
