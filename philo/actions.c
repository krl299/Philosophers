/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoran-l <cmoran-l@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:37:23 by cmoran-l          #+#    #+#             */
/*   Updated: 2023/05/23 16:19:28 by cmoran-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philosopher *philo)
{
	if (philo->forks < 2)
	{
		pthread_mutex_lock(philo->left_fork_mutex);
		printf("%lli %i has taken a fork\n", ft_get_current_time(philo->table->start_time), philo->id);
		philo->forks += 1;
		if (philo->table->num_philosophers > 1)
		{
			pthread_mutex_lock(philo->right_fork_mutex);
			printf("%lli %i has taken a fork\n", ft_get_current_time(philo->table->start_time), philo->id);
			philo->forks += 1;
		}
	}
	printf("%lli %i is eating\n", ft_get_current_time(philo->table->start_time), philo->id);
	philo->forks = 0;
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork_mutex);
	pthread_mutex_unlock(philo->right_fork_mutex);
	philo->eat_count += 1;
}

void	ft_sleep(t_philosopher *philo)
{
	printf("%lli %i is sleeping\n", ft_get_current_time(philo->table->start_time), philo->id);
	usleep(philo->table->time_to_sleep * 1000);
}

void	ft_think(t_philosopher *philo)
{
	printf("%lli %i is thinking\n", ft_get_current_time(philo->table->start_time), philo->id);
	usleep(10);
}

int	ft_die(t_philosopher *philo)
{
	int	dead_time;

	dead_time = philo->last_meal_time + philo->table->time_to_die;
	if (dead_time >= ft_get_current_time(philo->table->start_time))
	{
		pthread_mutex_lock(philo->table_mutex);
		philo->table->deaths += 1;
		philo->status = DEAD;
		pthread_mutex_unlock(philo->table_mutex);
		return (1);
	}
	else
		return (0);
}
