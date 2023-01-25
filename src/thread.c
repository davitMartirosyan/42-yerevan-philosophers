/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:09:44 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/25 17:31:32 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*philosopher(void *table)
{
	t_philo			*philo;

	philo = table;
	if ((philo->id % 2) != 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->fork[philo->rfork]);
		print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork[philo->lfork]);
		print(philo, "has taken a fork");
		is_eating(philo);
		pthread_mutex_unlock(&philo->fork[philo->lfork]);
		pthread_mutex_unlock(&philo->fork[philo->rfork]);
		print(philo, "is sleep");
		__usleep(philo->time_to_sleep);
		print(philo, "is thinking");
	}
	return (NULL);
}

void	print(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->print);
	printf("[%lld] Philosopher %d : %s\n", \
	(get_now() - philo->starttime), philo->id, action);
	pthread_mutex_unlock(philo->print);
}

void	is_eating(t_philo *philo)
{
	philo->last_eat_time = get_now();
	print(philo, "is eating");
	__usleep(philo->time_to_eat);
	if (philo->count_of_eating != -1
		&& philo->counter != philo->count_of_eating)
		philo->counter++;
}

int	create_threads(t_thread_table *table)
{
	int	i;

	i = -1;
	while (++i < table->vector[0])
	{
		table->philos[i].id = i + 1;
		table->philos[i].lfork = (i + 1) % table->vector[0];
		table->philos[i].rfork = i;
		table->philos[i].died = 0;
		table->philos[i].fork = table->forks;
		table->philos[i].time_to_die = table->vector[1];
		table->philos[i].time_to_eat = table->vector[2];
		table->philos[i].time_to_sleep = table->vector[3];
		table->philos[i].count_of_eating = table->optional_argument;
		table->philos[i].counter = 0;
		table->philos[i].last_eat_time = get_now();
		table->philos[i].starttime = get_now();
		table->philos[i].print = &table->print;
	}
	return (0);
}
