/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoran-l <cmoran-l@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 09:59:05 by cmoran-l          #+#    #+#             */
/*   Updated: 2023/05/18 17:04:22 by cmoran-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philosopher
{
	int				id;
	int				eat_count;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	last_meal_time;
	int				is_live;
	pthread_cond_t	death_cond;
	pthread_mutex_t	death_mutex;
}	t_philosopher;

typedef struct s_table
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	int				wrong_input;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;
}	t_table;

void	ft_check_arg(t_table *table, int argc, char *argv);
void	ft_cycle_of_live(t_table *table);
void	ft_create_forks(t_table *table, pthread_mutex_t *forks);
void	ft_create_philosophers(t_table *table, \
		t_philosopher *philosophers, pthread_mutex_t *forks);

//	UTILS
int		ft_atoi(char *str, t_table *table);
#endif
