/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoran-l <cmoran-l@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 09:59:05 by cmoran-l          #+#    #+#             */
/*   Updated: 2023/05/31 18:40:36 by cmoran-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define _DEFAULT_SOURCE
# define THINKING 1
# define EATING 2
# define SLEEPING 3
# define DEAD 4

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_table	t_table;
typedef struct s_philosopher
{
	int				id;
	int				status;
	int				eat_count;
	int				dead_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;
	long long		last_meal_time;
	t_table			*table;
}	t_philosopher;

typedef struct s_table
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	int				wrong_input;
	long long		start_time;
	int				filled;
	int				deaths;
	pthread_mutex_t	*table_mutex;
}	t_table;

//	MAIN.C
void		ft_check_arg(t_table *table, int argc, char *argv);
void		ft_cycle_of_live(t_table *table, t_philosopher *philosophers,
				pthread_mutex_t *forks);
void		*ft_philosophers_thread(void *arg);
void		*ft_single_philo_thread(void *arg);

//	CREATE.C
void		*ft_create_forks(t_table *table, pthread_mutex_t *forks);
void		*ft_create_philosophers(t_table *table, \
		t_philosopher *philosophers, pthread_mutex_t *forks);

//	CLEAR_TABLE.C
void		ft_clear_table(t_philosopher *philosophers, \
		pthread_mutex_t *forks, t_table *table);
//	ACTIONS.C
void		ft_eat(t_philosopher *philo);
void		ft_sleep(t_philosopher *philo);
void		ft_think(t_philosopher *philo);
int			ft_alive(t_philosopher *philo);

//	UTILS.C
int			ft_atoi(char *str, t_table *table);
long long	ft_get_time(void);
long long	ft_get_current_time(long long time);

void		ft_time_action(t_philosopher *philo, int time);
void		ft_print_action(t_philosopher *philo, int action);
#endif
