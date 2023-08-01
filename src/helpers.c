/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:08:33 by flauer            #+#    #+#             */
/*   Updated: 2023/08/01 10:19:04 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(t_philo *philo, char *msg)
{
	if (get_mutex(&philo->table->stop))
		return ;
	pthread_mutex_lock(&philo->table->out);
	printf("%li %i %s\n", get_timestamp(philo->table), philo->id, msg);
	pthread_mutex_unlock(&philo->table->out);
}

void	ft_err(t_table *table, char *msg)
{
	printf("Error\n");
	if (msg)
		printf("%s\n", msg);
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_isspace(const char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

/// @brief convert a string to an integer
/// @param str input string with decimal number
/// @return number as integer
ssize_t	ft_atoi(const char *str)
{
	ssize_t	ret;
	int		i;
	int		sign;

	ret = 0;
	i = 0;
	sign = 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		ret = (ret * 10) + (str[i] - '0');
		i++;
	}
	return (ret * sign);
}
