/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:03:04 by mehakcan          #+#    #+#             */
/*   Updated: 2024/10/10 17:03:05 by mehakcan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    print_status(t_philo *philo, const char *status)
{
    pthread_mutex_lock(&philo->table->print_lock);
    printf("%llu %d %s\n", get_time_in_ms() - philo->table->start_time, philo->id, status);
    pthread_mutex_unlock(&philo->table->print_lock);
}

void my_sleep(int time)
{
    uint64_t start = get_time_in_ms();
    while ((get_time_in_ms() - start) < (uint64_t)time)
        usleep(250);
}

void ft_putstr_fd(const char *s, int fd)
{
    write(fd, s, ft_strlen(s));
}