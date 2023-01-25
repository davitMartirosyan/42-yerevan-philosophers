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

t_thread_table	*create_philos_table(int ac, char **av)
{
	t_thread_table	*philos;

	philos = malloc(sizeof(t_thread_table));
	philos->n_args = collect(ac);
	philos->vector = push_back(philos->n_args, av);
	philos->optional_argument = 0;
	if (philos->n_args == (ARGUMENT_SUCCESS | OPTIONAL_TRUE))
		philos->optional_argument = philos->vector[philos->n_args - 1];
	if (!create_threads(philos))
		return (philos);
	return (NULL);
}

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
	int	c;

	i = -1;
	init_mutexes(table);
	while (++i < table->vector[0])
		pthread_create(&table->philos[i].thread_id, NULL,
			philosopher, (void *)&table->philos[i]);
	while (1)
	{
		c = -1;
		while (++c < table->vector[0])
		{
			if ((get_now() - table->philos[c].last_eat_time) > table->vector[1])
			{
				print(&table->philos[c], "was died");
				pthread_detach(table->philos[c].thread_id);
				return ;
			}
		}
	}
	__exit(table);
	return ;
}

void	__exit(t_thread_table *table)
{
	int	i;

	i = -1;
	while (++i < table->vector[0])
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->print);
}
