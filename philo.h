#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

typedef struct s_philo {
    int id;
    int left_fork;
    int right_fork;
    long last_meal_time;
    int meals_eaten;
    struct s_table *table;
}   t_philo;

typedef struct s_table {
    unsigned int num_philos;
    unsigned int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int philo_dead;
    uint64_t start_time;
    pthread_mutex_t mtx;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    pthread_mutex_t time;
    t_philo *philos;
}           t_table;

// main.c
int die_control(t_philo *philo);

// utils.c
int ft_atoi(const char *str);

// utils1.c
void    print_status(t_philo *philo, const char *status); // Değişiklik burada

// situation.c
void    take_forks(t_philo *philo);
void    put_forks(t_philo *philo);
void    eat(t_philo *philo);
void    sleep_and_think(t_philo *philo);
void    *philosopher_routine(void *arg);
void    *monitor_routine(void *arg);
int philo_check(t_philo *philo);

uint64_t get_time_in_ms(void);
void my_sleep(int time);


#endif