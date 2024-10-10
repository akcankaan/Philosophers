/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:53:33 by mehakcan          #+#    #+#             */
/*   Updated: 2024/10/10 17:06:18 by mehakcan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>

int init_mutex(t_table *table)
{
    unsigned int i;

    i = 0;
    table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->num_philos);
    if (!table->forks)
        return (1);
    while (i < table->num_philos)
    {
        if (pthread_mutex_init(&table->forks[i], NULL))
            return (error_init(table, i, 0));
        i++;
    }
    if (pthread_mutex_init(&table->print_lock, NULL))
        return (error_init(table, i, 0));
    if (pthread_mutex_init(&table->time, NULL))
        return (error_init(table, i, 1));
    if (pthread_mutex_init(&table->mtx, NULL))
        return (error_init(table, i, 2));
    return (0);
}

int init_philos(t_table *table)
{
    unsigned int i;

    i = -1;
    table->philos = (t_philo *)malloc(sizeof(t_philo) * table->num_philos);
    if (!table->philos)
        return (1);
    while (++i < table->num_philos)
    {
        table->philos[i].id = i + 1;
        table->philos[i].meals_eaten = 0;
        table->philos[i].last_meal_time = 0;
        table->philos[i].table = table;
        table->philos[i].left_fork = i;
        table->philos[i].right_fork = (i + 1) % table->num_philos;
    }
    return (0);
}

int init_table(t_table *table, int argc, char **argv)
{
    table->num_philos = ft_atoi(argv[1]);
    table->num_philos = atoi(argv[1]);
    table->time_to_die = atoi(argv[2]);
    table->time_to_eat = atoi(argv[3]);
    table->time_to_sleep = atoi(argv[4]);
    table->must_eat = -1;
    if (argc == 6)
        table->must_eat = atoi(argv[5]);
    table->philo_dead = 0;
    table->ready_count = table->num_philos;
    table->start_time = 0;
    table->philos = NULL;
    table->forks = NULL;
    if (init_mutex(table))
        return (1);
    if (init_philos(table))
        return (1);
    return (0);
}