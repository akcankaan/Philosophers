#include "philo.h"

int error_init(t_table *table, int len, int m_num)
{
    if (m_num > 0)
        pthread_mutex_destroy(&table->print_lock);
    else if (m_num > 1)
        pthread_mutex_destroy(&table->time);
    else if (m_num > 2)
        pthread_mutex_destroy(&table->mtx);
    while (--len >= 0)
        pthread_mutex_destroy(&table->start_time);
    if (table->forks)
        free(table->forks);
    return (1);
}

int  error_create(t_table *table, int len)
{
    pthread_mutex_lock(&table->start_time);
    while (--len >= 0)
        pthread_join(table->philos[len].thread, NULL);
    free_data(table);
    return (1);
}