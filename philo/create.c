/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoran-l <cmoran-l@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:59:50 by cmoran-l          #+#    #+#             */
/*   Updated: 2023/05/22 12:17:42 by cmoran-l         ###   ########.fr       */
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
		philosophers[i].status = THINKING;
		philosophers[i].eat_count = 0;
		philosophers[i].left_fork = &forks[i];
		if (table->num_philosophers != 1)
			philosophers[i].right_fork = &forks[(i + 1) % table->num_philosophers];
		philosophers[i].forks = 0;
	//	printf("Philosopher %i left:%i right:%i\n", philosophers[i].id, i, (i + 1) % table->num_philosophers);
		philosophers[i].table = table;
		philosophers[i].table->start_time = ft_get_time() + table->num_philosophers * 20;
		pthread_create(&philosophers[i].thread, NULL, \
		(void *)ft_philosophers_thread, &philosophers[i]);
		i++;
	}
	return ((void *)philosophers);
}
