/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:35:16 by mehakcan          #+#    #+#             */
/*   Updated: 2024/10/23 16:00:52 by mehakcan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long			last_meal_time;
	int				meals_eaten;
	pthread_t		thread;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	unsigned int	ready_count;
	unsigned int	num_philos;
	unsigned int	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				philo_dead;
	u_int64_t		start_time;
	pthread_mutex_t	mtx;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	time;
	t_philo			*philos;
}					t_table;

int					init_mutex(t_table *table);
int					init_philos(t_table *table);
int					init_table(t_table *table, int argc, char **argv);

int					free_table(t_table *table);
int					free_mutex(t_table *table);
int					error_create(t_table *table, int len);
int					error_init(t_table *table, int len, int m_num);

void				*control_dead(void *arg);
int					die_control(t_philo *philo);

int					ft_atoi(const char *str);
int					ft_strlen(const char *s);
int					ft_isdigit(int c);
int					arg_check(int argc, char **argv);

void				print_status(t_philo *philo, const char *status);
void				my_sleep(u_int64_t time);
void				ft_putstr_fd(const char *s, int fd);
u_int64_t			get_time_in_ms(void);

void				*philosopher_routine(void *arg);
int					philo_check(t_philo *philo);
int					philo_join(t_table *table);
int					philo_dead(t_philo *philo);

int					start_simulation(t_table *table);
void				take_forks(t_philo *philo);
void				put_forks(t_philo *philo);
void				eat(t_philo *philo);
void				sleep_and_think(t_philo *philo);

#endif