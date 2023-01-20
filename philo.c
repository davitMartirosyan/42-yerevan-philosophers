/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:09:08 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/19 16:28:02 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char **av)
{
	t_thread_table	*table;
	int				n_args;

	(void)table;
	n_args = collect(ac);
	if (n_args == ARGUMENT_ERROR)
	{
		printf("error\n");
		return (1);
	}
	table = create_philos_table(ac, av);
	if(table)
		init(table);
	return (-1);
}

t_thread_table	*create_philos_table(int ac, char **av)
{
	t_thread_table	*philos;

	philos = malloc(sizeof(t_thread_table));
	philos->n_args = collect(ac);
	philos->vector = push_back(philos->n_args, av);
	if (philos->n_args == (ARGUMENT_SUCCESS | OPTIONAL_TRUE))
		philos->optional_argument = philos->vector[philos->n_args - 1];
	else
		philos->optional_argument = -1;
	if (create_threads(philos))
		return (philos);
	return (NULL);
}

int	create_threads(t_thread_table *table)
{
	int	i;

	i = table->vector[0];
	while (--i >= 0)
	{
		table->philos[i].id = i + 1;
		table->philos[i].lfork = i;
		table->philos[i].rfork = (i + 1) % table->vector[0];
		table->philos[i].thread_table = table;
	}
	return (1);
}
