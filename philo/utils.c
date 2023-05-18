/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoran-l <cmoran-l@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:39:22 by cmoran-l          #+#    #+#             */
/*   Updated: 2023/05/18 17:03:58 by cmoran-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str, t_table *table)
{
	long long int	nbr;
	int				i;

	nbr = 0;
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		table->wrong_input = 1;
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	if (nbr > INT_MAX || nbr < INT_MIN)
		table->wrong_input = 1;
	return (nbr);
}
