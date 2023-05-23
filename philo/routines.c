/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoran-l <cmoran-l@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:25:55 by cmoran-l          #+#    #+#             */
/*   Updated: 2023/05/23 16:45:46 by cmoran-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_single_philo_thread(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->table->num_times_to_eat == 0)
		return (NULL);
	if (philo->table->time_to_die == 0)
		return (NULL);
	philo->last_meal_time = ft_get_current_time(philo->table->start_time);
	while (philo->table->start_time < ft_get_time())
		usleep(1);
	pthread_mutex_lock(philo->left_fork_mutex);
	printf("%lli %i has taken a fork\n", ft_get_current_time(philo->table->start_time), philo->id);
	usleep(philo->last_meal_time + philo->table->time_to_die * 1000)	;
	printf("%lli %i is died\n", ft_get_current_time(philo->table->start_time), philo->id);
	return (NULL);
}

void	*ft_philosophers_thread(void *arg)
{
	t_philosopher *philo;
	long long	time;

	philo = (t_philosopher *)arg;
	philo->last_meal_time = ft_get_time();
	time = philo->last_meal_time - philo->table->start_time;
	while (time < 0)
	{
		time = ft_get_current_time(philo->table->start_time);
		philo->last_meal_time = time;
	}
//	printf("Philosopher %i is here with time: %lli!!\n", philo->id, time);
	//printf("Philosopher %i Status %i!!\n", philo->id, philo->status);
//	printf("Philosopher %i forks %i!!\n", philo->id, philo->forks);
	while (1)
	{
		if (philo->status == THINKING)
		{
			ft_eat(philo);
			philo->status += 1;
		}
		else if (philo->status == EATING)
		{
			ft_sleep(philo);
			philo->status += 1;
		}
		else if (philo->status == SLEEPING)
		{
			ft_think(philo);
			philo->status = THINKING;			
		}
		else if (philo->status == DEAD)
			printf("%lli %i is died\n", ft_get_current_time(philo->table->start_time), philo->id);
	}
	return (NULL);
}