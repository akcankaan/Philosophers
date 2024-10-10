#include "../philo.h"

void take_forks(t_philo *philo) {
    pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
    print_status(philo, "has taken the left fork");
    pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
    print_status(philo, "has taken the right fork");
}

void put_forks(t_philo *philo) {
    pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
    pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}

void eat(t_philo *philo) {
    t_table *table = philo->table;

    // Çatalları al
    take_forks(philo);

    // Yemek yeme
    print_status(philo, "is eating");

    philo->last_meal_time = get_time_in_ms();
    my_sleep(table->time_to_eat);
    philo->meals_eaten++;

    // Çatalları bırak
    put_forks(philo);
}


void sleep_and_think(t_philo *philo) {
    print_status(philo, "is sleeping");
    my_sleep(philo->table->time_to_sleep);
    print_status(philo, "is thinking");
}

int philo_dead(t_philo *philo) 
{
    pthread_mutex_lock(&philo->table->print_lock);
    philo->table->philo_dead = 1;
    pthread_mutex_unlock(&philo->table->print_lock);
    printf("%llu %d is died\n", get_time_in_ms() - philo->table->start_time, philo->id);
    return (1);
}

int philo_check(t_philo *philo) 
{
    pthread_mutex_lock(&philo->table->time);
    if (philo->last_meal_time == 0)
        philo->last_meal_time = philo->table->start_time;
    if (philo->table->time_to_die <= get_time_in_ms() - philo->last_meal_time)
        return (pthread_mutex_unlock(&philo->table->time), philo_dead(philo));
    pthread_mutex_unlock(&philo->table->time);
    return (0);
}
int philo_join(t_table *table)
{
    unsigned int i;
    int exit_code;

    exit_code = 0;
    table->start_time = get_time_in_ms();
    while (1)
    {
        pthread_mutex_lock(&table->mtx);
        if (table->ready_count == table->num_philos)
        {
            pthread_mutex_unlock(&table->mtx);
            break;
        }
        pthread_mutex_unlock(&table->mtx);
    }
    i = -1;
    while (++i < table->num_philos)
        if (pthread_join(table->philos[i].thread, NULL))
            exit_code = 1;
    return (exit_code);
}
void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2)
        my_sleep(philo->table->time_to_eat / 2);
    while (1)
    {
        eat(philo);
        sleep_and_think(philo);
        if (die_control(philo))
            break;
        if (philo->table->must_eat > 0 && philo->meals_eaten == philo->table->must_eat)
        {
            pthread_mutex_lock(&philo->table->print_lock);
            philo->table->ready_count--;
            pthread_mutex_unlock(&philo->table->print_lock);
        }
    }
    return (NULL);
}

uint64_t get_time_in_ms() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

