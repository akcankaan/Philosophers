/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:42:35 by mehakcan          #+#    #+#             */
/*   Updated: 2024/10/18 15:48:39 by mehakcan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

int	die_control(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	if (philo->table->ready_count == 0)
		philo->table->philo_dead = 1;
	if (philo->table->philo_dead)
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->print_lock);
	return (0);
}

void	*control_dead(void *arg)
{
	unsigned int	i;
	t_table			*table;

	table = arg;
	while (!table->philo_dead)
	{
		i = -1;
		while (++i < table->num_philos)
		{
			if (die_control(&table->philos[i]))
				break ;
			if (philo_check(&table->philos[i]))
				break ;
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), 1);
	else if (init_table(&table, argc, argv))
		return (ft_putstr_fd("Error: initalization failed\n", 2), 1);
	else if (start_simulation(&table))
		return (ft_putstr_fd("Error: simulation failed\n", 2), 1);
	free_table(&table);
	return (0);
}
