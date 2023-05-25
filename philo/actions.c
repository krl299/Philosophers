/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoran-l <cmoran-l@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:37:23 by cmoran-l          #+#    #+#             */
/*   Updated: 2023/05/25 13:55:47 by cmoran-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philosopher *philo)
{
	if (ft_alive(philo) == 0)
		return ;
	pthread_mutex_lock(philo->table->table_wr_mutex);
	pthread_mutex_lock(philo->left_fork_mutex);
	printf("%lli %i has taken a fork\n", ft_get_current_time(philo->table->start_time), philo->id);
	philo->forks += 1;
	pthread_mutex_lock(philo->right_fork_mutex);
	printf("%lli %i has taken a fork\n", ft_get_current_time(philo->table->start_time), philo->id);
	philo->forks += 1;
	philo->last_meal_time = ft_get_current_time(philo->table->start_time);
	printf("%lli %i is eating\n", ft_get_current_time(philo->table->start_time), philo->id);
	pthread_mutex_unlock(philo->table->table_wr_mutex);
	philo->forks = 0;
	usleep(philo->table->time_to_eat * 1000);
	philo->eat_count += 1;
	if (philo->eat_count == philo->table->num_times_to_eat)
	{
		pthread_mutex_lock(philo->table->table_mutex);
		philo->table->filled += 1;
		pthread_mutex_unlock(philo->table->table_mutex);
	}
	pthread_mutex_unlock(philo->left_fork_mutex);
	pthread_mutex_unlock(philo->right_fork_mutex);
}

void	ft_sleep(t_philosopher *philo)
{
	pthread_mutex_lock(philo->table->table_wr_mutex);
	printf("%lli %i is sleeping\n", ft_get_current_time(philo->table->start_time), philo->id);
	pthread_mutex_unlock(philo->table->table_wr_mutex);
	usleep(philo->table->time_to_sleep * 1000);
}

void	ft_think(t_philosopher *philo)
{
	pthread_mutex_lock(philo->table->table_wr_mutex);
	printf("%lli %i is thinking\n", ft_get_current_time(philo->table->start_time), philo->id);
	pthread_mutex_unlock(philo->table->table_wr_mutex);
	usleep(5000);
}

int	ft_alive(t_philosopher *philo)
{
	int	dead_time;

	dead_time = philo->last_meal_time + philo->table->time_to_die;
	pthread_mutex_lock(philo->table->table_mutex);
	if (philo->table->deaths > 0 || philo->table->filled == philo->table->num_philosophers)
		return (0);
	if (ft_get_current_time(philo->table->start_time) <= dead_time)
	{
	pthread_mutex_unlock(philo->table->table_mutex);
		return (1);
	}
	philo->table->deaths += 1;
	philo->status = DEAD;
	return (0);
}
