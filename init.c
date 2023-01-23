/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 02:26:37 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/23 18:59:23 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_thread_table	*create_philos_table(int ac, char **av)
{
	t_thread_table	*philos;
	char			*vars;

	vars = "Philosophers:Time_To_Die:Time_To_Eat:Time_To_Sleep:Must_To_Eat";
	philos = malloc(sizeof(t_thread_table));
	philos->n_args = collect(ac);
	philos->vector = push_back(philos->n_args, av);
	if (philos->vector[0] < 2)
	{
		printf("Invalid Arguments: The Count of <%s> Must greather than %d\n",
			philos->argument_names[0], philos->vector[0]);
		return (NULL);
	}
	if (philos->vector[1] < 0 || philos->vector[2] < 0
		|| philos->vector[3] < 0
		|| (philos->vector[4] && philos->vector[4] < 0))
	{
		printf("Invalid Arguments: The Count of <%s> Must greather than %d\n",
			philos->argument_names[fnd(philos->vector, philos->n_args)],
			philos->vector[fnd(philos->vector, philos->n_args)]);
		return (NULL);
	}
	philos->optional_argument = -1;
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
	while (++i < philos->vector[0])
		if (pthread_mutex_init(&philos->forks[i], NULL))
			return (1);
	return (0);
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
		table->philos[i].table = table;
		table->philos[i].print = &table->print;
	}
	return (0);
}

void	init(t_thread_table *table)
{
	int				i;
	struct timeval	smt;

	i = -1;
	pthread_mutex_init(&table->print, NULL);
	while (++i < table->vector[0])
	{
		pthread_create(&table->philos[i].thread_id, NULL,
			philosopher, (void *)&table->philos[i]);
		gettimeofday(&smt, NULL);
		table->philos[i].last_eat_time = smt.tv_sec;
	}
	i = -1;
	while (++i < table->vector[0])
		pthread_join(table->philos[i].thread_id, NULL);
	pthread_mutex_destroy(&table->print);
}
