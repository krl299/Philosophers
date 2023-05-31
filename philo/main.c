/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoran-l <cmoran-l@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 09:57:13 by cmoran-l          #+#    #+#             */
/*   Updated: 2023/05/31 16:28:38 by cmoran-l         ###   ########.fr       */
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
		table->deaths = 0;
	}
	else
		table->wrong_input = 1;
}

// funcion muy larga
void	ft_cycle_of_live(t_table *table, t_philosopher *philosophers,
		pthread_mutex_t *forks)
{
	int	i;

	table->start_time = ft_get_time() + (table->num_philosophers * 20);
	table->table_mutex = malloc(sizeof(pthread_mutex_t));
	i = 0;
	if (table->num_philosophers == 1)
	{
		table->start_time = ft_get_time();
		if (pthread_create(&philosophers[i].thread, NULL, \
		(void *)ft_single_philo_thread, &philosophers[i]) != 0)
			printf("Error creating thread.");
		pthread_join(philosophers[i].thread, NULL);
		ft_clear_table(philosophers, forks, table);
		return ;
	}
	while (i < table->num_philosophers)
	{
		pthread_mutex_init(table->table_mutex, NULL);
		pthread_create(&philosophers[i].thread, NULL, \
		(void *)ft_philosophers_thread, &philosophers[i]);
		i++;
	}
	while(1)
	{
		if (i == table->num_philosophers)
			i = 0;
		if (ft_alive(&philosophers[i]) == 0)
			break ;
		usleep(500);
		i++;
	}
	usleep(1500);
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
	ft_clear_table(philosophers, forks, table);
}

static void	ft_leaks(void)
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	t_table			table;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;

	atexit(ft_leaks);
	table.wrong_input = 0;
	ft_check_args(&table, argc, argv);
	if (argc < 5 || argc > 6 || table.wrong_input == 1)
	{
		ft_wrong_input();
		return (1);
	}
	forks = NULL;
	forks = ft_create_forks(&table, forks);
	philosophers = NULL;
	philosophers = ft_create_philosophers(&table, philosophers, forks);
	table.filled = 0;
	ft_cycle_of_live(&table, philosophers, forks);
	return (0);
}
