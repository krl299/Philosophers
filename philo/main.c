/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoran-l <cmoran-l@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 09:57:13 by cmoran-l          #+#    #+#             */
/*   Updated: 2023/05/18 17:24:21 by cmoran-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_wrong_input(void)
{
	printf("Usage: ./philo <number_of_philosophers> <time_to_die>");
	printf(" <time_to_eat> <time_to_sleep> ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	printf("Numbers must be in the INT range\n");
}

void	ft_check_args(t_table *table, int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		table->num_philosophers = ft_atoi(argv[1], table);
		table->time_to_die = ft_atoi(argv[2], table);
		table->time_to_eat = ft_atoi(argv[3], table);
		table->time_to_sleep = ft_atoi(argv[4], table);
		if (argc == 6)
			table->num_times_to_eat = ft_atoi(argv[5], table);
		else
			table->num_times_to_eat = -1;
	}
	else
		table->wrong_input = 1;
}

void	ft_create_forks(t_table *table, pthread_mutex_t *forks)
{
	int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->num_philosophers);
	if (!forks)
		return ;
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	*philosophers_thread(void *arg)
{
	(void)arg;
	return (NULL);
}

void	ft_create_philosophers(t_table *table, \
		t_philosopher *philosophers, pthread_mutex_t *forks)
{
	int	i;

	philosophers = malloc(sizeof(t_philosopher) * table->num_philosophers);
	if (!philosophers)
		return ;
	i = 0;
	while (i < table->num_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].eat_count = 0;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % table->num_philosophers];
		gettimeofday(&philosophers[i].last_meal_time, NULL);
		philosophers[i].is_live = 1;
		pthread_cond_init(&philosophers[i].death_cond, NULL);
		pthread_mutex_init(&philosophers[i].death_mutex, NULL);
//		pthread_create(&philosophers[i].thread, NULL, \
//		philosophers_thread, &philosophers[i]);
		i++;
	}	
}

void	ft_cycle_of_live(t_table *table)
{
	t_philosopher		*philosophers;
	pthread_mutex_t		*forks;
	int					i;

	forks = NULL;
	philosophers = NULL;
	ft_create_forks(table, forks);
	ft_create_philosophers(table, philosophers, forks);
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_join(philosophers[i].thread, NULL);
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	table.wrong_input = 0;
	ft_check_args(&table, argc, argv);
	if (argc < 5 || argc > 6 || table.wrong_input == 1)
	{
		ft_wrong_input();
		return (1);
	}
	ft_cycle_of_live(&table);
	return (0);
}
