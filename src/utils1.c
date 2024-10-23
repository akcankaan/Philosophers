/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:03:04 by mehakcan          #+#    #+#             */
/*   Updated: 2024/10/23 16:11:53 by mehakcan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void	print_status(t_philo *philo, const char *status)
{
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo->table->philo_dead)
	{
		printf("%llu %d %s\n", get_time_in_ms() - philo->table->start_time,
			philo->id, status);
	}
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	my_sleep(u_int64_t time)
{
	u_int64_t	start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < time)
		usleep(250);
}

void	ft_putstr_fd(const char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

u_int64_t	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
