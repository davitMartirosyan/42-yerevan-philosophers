/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:09:44 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/24 13:50:14 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*philosopher(void *table)
{
	t_philo			*philo;

	philo = table;
	if ((philo->id % 2) != 0)
		__usleep(1000);
	while (!philo->died)
	{
		printf("%d -> %lld : %lld : [%d]\n", philo->id, philo->last_eat_time, get_now(), philo->time_to_die);
		pthread_mutex_lock(&philo->fork[min_fork(philo->lfork, philo->rfork)]);
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

void	is_eating(t_philo *philo)
{
	print(philo, "is eating");
	__usleep(philo->time_to_eat);
	if (philo->count_of_eating != -1
		&& philo->counter != philo->count_of_eating)
		philo->counter++;
	philo->last_eat_time = get_now();
}

int	create_threads(t_thread_table *table)
{
	int				i;

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