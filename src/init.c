/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 02:26:37 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/24 13:50:05 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_thread_table	*create_philos_table(int ac, char **av)
{
	t_thread_table	*philos;

	philos = malloc(sizeof(t_thread_table));
	philos->n_args = collect(ac);
	philos->vector = push_back(philos->n_args, av);
	philos->optional_argument = 0;
	if (philos->n_args == (ARGUMENT_SUCCESS | OPTIONAL_TRUE))
		philos->optional_argument = philos->vector[philos->n_args - 1];
	if (!init_mutexes(philos) && !create_threads(philos))
		return (philos);
	return (NULL);
}

int	init_mutexes(t_thread_table *philos)
{
	int	i;

	i = -1;
	pthread_mutex_init(&philos->print, NULL);
	pthread_mutex_init(&philos->check_dead, NULL);
	while (++i < philos->vector[0])
		if (pthread_mutex_init(&philos->forks[i], NULL))
			return (1);
	return (0);
}

void	init(t_thread_table *table)
{
	int	i;
	int	c;

	i = -1;
	while (++i < table->vector[0])
	{
		pthread_create(&table->philos[i].thread_id, NULL, philosopher, (void *)&table->philos[i]);
		pthread_detach(table->philos[i].thread_id);
	}
	while(1)
	{
		c = -1;
		while (++c < table->vector[0])
		{
			if ((get_now() - table->philos[c].last_eat_time) > table->philos[c].time_to_die)
			{
				printf("%lld : %lld\n", table->philos[c].last_eat_time, get_now());
				print(&table->philos[c], "was died");
				return ;
			}
		}
	}
	i = -1;
	while (++i < table->vector[0])
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->check_dead);
	return ;
}

void	__is_dead(t_thread_table *table)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < table->vector[0])
		{
			pthread_mutex_lock(&table->check_dead);
			if ((get_now() - table->philos[i].last_eat_time) > table->philos[i].time_to_die)
			{
				print(&table->philos[i], "\n\n\n\n\n\nwas died\n\n\n\n\n\n\n");
				table->philos[i].died = 1;
				return ;
			}
			pthread_mutex_unlock(&table->check_dead);
		}
	}
}

void	__exit(t_thread_table *table)
{
	int	i;
	int	c;

	c = -1;
	while (++c < table->vector[0])
		pthread_join(table->philos[c].thread_id, NULL);
	i = -1;
	while (++i < table->vector[0])
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->check_dead);
}