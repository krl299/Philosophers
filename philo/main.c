/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoran-l <cmoran-l@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 09:57:13 by cmoran-l          #+#    #+#             */
/*   Updated: 2023/05/22 15:03:53 by cmoran-l         ###   ########.fr       */
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
		printf("deaths:%d\n", table->deaths);
	}
	else
		table->wrong_input = 1;
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

void	ft_cycle_of_live(t_table *table)
{
	t_philosopher		*philosophers;
	pthread_mutex_t		*forks;
	int					i;

	forks = NULL;
	philosophers = NULL;
	forks = ft_create_forks(table, forks);
	philosophers = ft_create_philosophers(table, philosophers, forks);
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
	t_table	table;

	atexit(ft_leaks);
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
