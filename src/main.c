/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:42:35 by mehakcan          #+#    #+#             */
/*   Updated: 2024/11/04 13:39:48 by mehakcan         ###   ########.fr       */
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
	while (1)
	{
		i = -1;
		while (++i < table->num_philos)
		{
			if (die_control(&table->philos[i]))
				break ;
			if (philo_check(&table->philos[i]))
				break ;
		}
		pthread_mutex_lock(&table->print_lock);
		if (table->philo_dead)
		{
			pthread_mutex_unlock(&table->print_lock);
			break ;
		}
		pthread_mutex_unlock(&table->print_lock);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), 1);
	else if (arg_check(argc, argv))
		return (ft_putstr_fd("Error: invalid arguments\n", 2), 1);
	else if (init_table(&table, argc, argv))
		return (ft_putstr_fd("Error: initalization failed\n", 2), 1);
	else if (start_simulation(&table))
		return (ft_putstr_fd("Error: simulation failed\n", 2), 1);
	free_table(&table);
	return (0);
}
