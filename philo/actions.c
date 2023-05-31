/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoran-l <cmoran-l@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:37:23 by cmoran-l          #+#    #+#             */
/*   Updated: 2023/05/31 16:38:17 by cmoran-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_time_action(t_philosopher *philo, int time)
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

static void	ft_print_action(t_philosopher *philo, int action)
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

// funcion muy larga
void	ft_eat(t_philosopher *philo)
{
	if (ft_alive(philo) == 0)
		return ;
	pthread_mutex_lock(philo->left_fork_mutex);
	if (!ft_alive(philo))
	{
		pthread_mutex_unlock(philo->left_fork_mutex);
		return ;
	}
	ft_print_action(philo, 0);
	pthread_mutex_lock(philo->right_fork_mutex);
	if (!ft_alive(philo))
	{
		pthread_mutex_unlock(philo->left_fork_mutex);
		pthread_mutex_unlock(philo->right_fork_mutex);
		return ;
	}
	ft_print_action(philo, 0);
	philo->last_meal_time = ft_get_current_time(philo->table->start_time);
	ft_print_action(philo, 1);
	ft_time_action(philo, philo->table->time_to_eat);
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
	if (ft_alive(philo) == 0)
		return ;
	if (philo->table->time_to_sleep == 0)
		return ;
	ft_print_action(philo, 2);
	ft_time_action(philo, philo->table->time_to_sleep);
}

void	ft_think(t_philosopher *philo)
{
	int	time_to_think;

	time_to_think = (philo->table->time_to_die - philo->table->time_to_eat
		- philo->table->time_to_sleep) / 2;
	if (time_to_think < 0)
		time_to_think = 5;
	if (ft_alive(philo) == 0)
		return ;
	ft_print_action(philo, 3);
	ft_time_action(philo, time_to_think);
}

// funcion muy larga
int	ft_alive(t_philosopher *philo)
{
	pthread_mutex_lock(philo->table->table_mutex);
	philo->dead_time = philo->last_meal_time + philo->table->time_to_die;
	if (philo->table->deaths == 1)
	{
		pthread_mutex_unlock(philo->table->table_mutex);
		return (0);
	}
	else if (philo->table->filled == philo->table->num_philosophers)
	{
		pthread_mutex_unlock(philo->table->table_mutex);
		return (0);
	}		
	else if (ft_get_current_time(philo->table->start_time) >= philo->dead_time)
	{
		if (philo->table->deaths == 0)
			ft_print_action(philo, 4);
		philo->table->deaths = 1;
		philo->status = DEAD;
		pthread_mutex_unlock(philo->table->table_mutex);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(philo->table->table_mutex);
		return (1);
	}
}
