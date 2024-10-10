/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:58:41 by mehakcan          #+#    #+#             */
/*   Updated: 2024/10/10 17:03:01 by mehakcan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int start_simulation(t_table *table)
{
    unsigned int i;
    pthread_t thread;
    table->start_time = get_time_in_ms();
    i = -1;
    if (pthread_create(&thread, NULL, control_dead, table))
        return (1);
    else
        while (++i < table->num_philos)
            if (pthread_create(&table->philos[i].thread, NULL, philosopher_routine, &table->philos[i]))
                return (error_create(table, i));
    if (pthread_join(thread, NULL))
        return (1);
    return (0);
}