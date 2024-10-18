/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:58:41 by mehakcan          #+#    #+#             */
/*   Updated: 2024/10/18 15:21:27 by mehakcan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	take_forks(philo);
	print_status(philo, "is eating");
	pthread_mutex_lock(&table->time);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&table->time);
	my_sleep(table->time_to_eat);
	philo->meals_eaten++;
	put_forks(philo);
}

void	sleep_and_think(t_philo *philo)
{
	print_status(philo, "is sleeping");
	my_sleep(philo->table->time_to_sleep);
	print_status(philo, "is thinking");
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	print_status(philo, "has taken the left fork");
	pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
	print_status(philo, "has taken the right fork");
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}

int	start_simulation(t_table *table)
{
	unsigned int	i;
	pthread_t		thread;

	table->start_time = get_time_in_ms();
	i = -1;
	if (pthread_create(&thread, NULL, control_dead, table))
		return (1);
	else
		while (++i < table->num_philos)
			if (pthread_create(&table->philos[i].thread, NULL,
					philosopher_routine, &table->philos[i]))
				return (error_create(table, i));
	if (philo_join(table))
		return (1);
	if (pthread_join(thread, NULL))
		return (1);
	return (0);
}
