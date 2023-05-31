/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoran-l <cmoran-l@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:39:22 by cmoran-l          #+#    #+#             */
/*   Updated: 2023/05/31 18:40:58 by cmoran-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str, t_table *table)
{
	long long int	nbr;
	int				i;

	nbr = 0;
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		table->wrong_input = 1;
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	if (nbr > INT_MAX || nbr < 0)
		table->wrong_input = 1;
	return (nbr);
}

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long long	ft_get_current_time(long long time)
{
	return (ft_get_time() - time);
}

void	ft_time_action(t_philosopher *philo, int time)
{
	long long int	time_end_action;

	time_end_action = ft_get_current_time(philo->table->start_time) + time;
	while (ft_get_current_time(philo->table->start_time) < time_end_action)
	{
		if (ft_alive(philo) == 0)
			break ;
		usleep(500);
	}
}

void	ft_print_action(t_philosopher *philo, int action)
{
	if (action == 0)
	{
		printf("%lli %i has taken a fork\n",
			ft_get_current_time(philo->table->start_time), philo->id);
	}
	else if (action == 1)
	{
		printf("%lli %i is eating\n",
			ft_get_current_time(philo->table->start_time), philo->id);
	}
	else if (action == 2)
	{
		printf("%lli %i is sleeping\n",
			ft_get_current_time(philo->table->start_time), philo->id);
	}
	else if (action == 3)
	{
		printf("%lli %i is thinking\n",
			ft_get_current_time(philo->table->start_time), philo->id);
	}
	else if (action == 4)
	{
		printf("%lli %i died\n",
			ft_get_current_time(philo->table->start_time), philo->id);
	}
}
