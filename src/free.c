/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:43:20 by mehakcan          #+#    #+#             */
/*   Updated: 2024/10/11 13:43:27 by mehakcan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>

int	free_table(t_table *table)
{
	int	exit_code;

	exit_code = 0;
	if (free_mutex(table))
		exit_code = 1;
	if (table->philos)
		free(table->philos);
	return (exit_code);
}

int	free_mutex(t_table *table)
{
	unsigned int	i;
	int				exit_code;

	i = 0;
	exit_code = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_destroy(&table->forks[i]))
			exit_code = 1;
		i++;
	}
	if (pthread_mutex_destroy(&table->print_lock))
		exit_code = 1;
	if (pthread_mutex_destroy(&table->time))
		exit_code = 1;
	if (pthread_mutex_destroy(&table->mtx))
		exit_code = 1;
	if (table->forks)
		free(table->forks);
	return (exit_code);
}

int	error_init(t_table *table, int len, int m_num)
{
	if (m_num > 0)
		pthread_mutex_destroy(&table->print_lock);
	else if (m_num > 1)
		pthread_mutex_destroy(&table->time);
	else if (m_num > 2)
		pthread_mutex_destroy(&table->mtx);
	while (--len >= 0)
		pthread_mutex_destroy(&table->forks[len]);
	if (table->forks)
		free(table->forks);
	return (1);
}

int	error_create(t_table *table, int len)
{
	while (--len >= 0)
		pthread_join(table->philos[len].thread, NULL);
	free_table(table);
	return (1);
}
