/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 02:26:37 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/25 17:31:43 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	init_mutexes(t_thread_table *philos)
{
	int	i;

	i = -1;
	pthread_mutex_init(&philos->print, NULL);
	while (++i < philos->vector[0])
		if (pthread_mutex_init(&philos->forks[i], NULL))
			return (1);
	return (0);
}

void	init(t_thread_table *table)
{
	int	i;

	i = -1;
	init_mutexes(table);
	while (++i < table->vector[0])
		pthread_create(&table->philos[i].thread_id, NULL,
			philosopher, (void *)&table->philos[i]);
	if (check_threads(table))
	{
		__exit(table);
		return ;
	}
	return ;
}

int	check_threads(t_thread_table *table)
{
	int	c;

	while (1)
	{
		if (table->optional_argument != -1 && check_all_ate(table) != -1)
		{
			pthread_mutex_lock(&table->print);
			printf("Simulation Stopped!\n");
			return (1);
		}
		c = -1;
		while (++c < table->vector[0])
		{
			if ((get_now() - table->philos[c].last_eat_time) > table->vector[1])
			{
				print(&table->philos[c], "was died");
				pthread_detach(table->philos[c].thread_id);
				return (1);
			}
		}
	}
	return (0);
}

int	check_all_ate(t_thread_table *table)
{
	int	i;

	i = -1;
	while (++i < table->vector[0])
	{
		if (table->philos[i].counter < table->optional_argument)
			return (-1);
	}
	return (0);
}

void	__exit(t_thread_table *table)
{
	int	i;

	i = -1;
	while (++i < table->vector[0])
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->print);
}
