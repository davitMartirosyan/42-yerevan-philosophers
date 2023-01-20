/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:09:44 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/19 15:19:38 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*philosopher(void *threads_table)
{
	t_philo	*philo;

	philo = threads_table;
	usleep(philo->thread_table->vector[1]);
	pthread_mutex_lock(&philo->thread_table->mutex_eat);
	printf("Philosopher %d, started to eat\n", philo->id);
	printf("left fork : %d\n", philo->lfork);
	printf("right fork:  %d\n", philo->rfork);
	usleep(philo->thread_table->vector[2]);
	printf("Philosopher %d, started to sleep\n\n", philo->id);
	pthread_mutex_unlock(&philo->thread_table->mutex_eat);
	return (NULL);
}

void	init(t_thread_table *table)
{
	int	i;

	i = table->vector[0];
	pthread_mutex_init(&table->mutex_eat, NULL);
	while (--i >= 0)
		pthread_create(&table->philos[i].thread_id, NULL, philosopher, \
		(void *)&table->philos[i]);
	i = 0;

	while (i <= table->vector[0])
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	pthread_mutex_destroy(&table->mutex_eat);
}