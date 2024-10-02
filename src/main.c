#include "../philo.h"
#include <stdio.h>

int die_control(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->print_lock);
    pthread_mutex_lock(&philo->table->mtx);
    if (philo->table->philo_dead)
    {
        pthread_mutex_unlock(&philo->table->print_lock);
        return (1);
    }
    pthread_mutex_unlock(&philo->table->print_lock);
    return (0);
}

void    *control_dead(void *arg)
{
    unsigned int i;
    t_table *table;

    table = arg;
    while (1)
    {
        i = -1;
        while (++i < table->num_philos)
        {
            if (die_control(&table->philos[i]))
                break;
            if (philo_check(&table->philos[i]))
                break;
        }
        if (i != table->num_philos)
            break;
    }
    return (NULL);
}


int main(int argc, char **argv) {
    if (argc != 5) {
        printf("Usage: %s num_philos time_to_die time_to_eat time_to_sleep\n", argv[0]);
        return 1;
    }

    t_table table;
    table.num_philos = atoi(argv[1]);
    table.time_to_die = atoi(argv[2]);
    table.time_to_eat = atoi(argv[3]);
    table.time_to_sleep = atoi(argv[4]);

    table.forks = malloc(sizeof(pthread_mutex_t) * table.num_philos);
    unsigned int i = 0;
    while (i < table.num_philos) {
        pthread_mutex_init(&table.forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&table.print_lock, NULL);

    t_philo *philos = malloc(sizeof(t_philo) * table.num_philos);
    pthread_t *threads = malloc(sizeof(pthread_t) * table.num_philos);

    i = 0;
    table.start_time = get_time_in_ms();
    while (i < table.num_philos) {
        philos[i].id = i + 1;
        philos[i].left_fork = i;
        philos[i].right_fork = (i + 1) % table.num_philos;
        philos[i].last_meal_time = get_time_in_ms();
        philos[i].meals_eaten = 0;
        philos[i].table = &table;
        pthread_create(&threads[i], NULL, philosopher_routine, &philos[i]);
        i++;
    }
    control_dead(&table);
    i = 0;
    while (i < table.num_philos) {
        pthread_join(threads[i], NULL);
        i++;
    }

    i = 0;
    while (i < table.num_philos) {
        pthread_mutex_destroy(&table.forks[i]);
        i++;
    }
    pthread_mutex_destroy(&table.print_lock);
    free(table.forks);
    free(philos);
    free(threads);

    return 0;
}