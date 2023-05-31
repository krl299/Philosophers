/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoran-l <cmoran-l@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:59:50 by cmoran-l          #+#    #+#             */
/*   Updated: 2023/05/31 15:04:57 by cmoran-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	*ft_create_forks(t_table *table, pthread_mutex_t *forks)
{
	int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->num_philosophers);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return ((void *)forks);
}

void	*ft_create_philosophers(t_table *table, \
		t_philosopher *philosophers, pthread_mutex_t *forks)
{
	int	i;

	philosophers = malloc(sizeof(t_philosopher) * table->num_philosophers);
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < table->num_philosophers)
	{
		philosophers[i].id = i + 1;
		if (philosophers[i].id % 2)
		{
			philosophers[i].status = THINKING;
		}
		else
			philosophers[i].status = 0;
		philosophers[i].eat_count = 0;
		philosophers[i].left_fork_mutex = &forks[i];
		philosophers[i].right_fork_mutex = &forks[(i + 1)
			% table->num_philosophers];
		philosophers[i].table = table;
		i++;
	}
	return ((void *)philosophers);
}
