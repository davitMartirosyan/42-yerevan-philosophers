/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:09:08 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/24 13:05:39 by dmartiro         ###   ########.fr       */
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
	if (!table || invalid_arguments(table))
		return (-1);
	init(table);
	return (-1);
}

int	collect(int ac)
{
	int	count_of_args;

	count_of_args = 0;
	if (ac == 6)
		count_of_args = (ARGUMENT_SUCCESS | OPTIONAL_TRUE);
	else if (ac == 5)
		count_of_args = ARGUMENT_SUCCESS;
	else if (ac > 6 || ac < 5)
		count_of_args = (int)ARGUMENT_ERROR;
	return (count_of_args);
}

t_thread_table	*create_philos_table(int ac, char **av)
{
	t_thread_table	*philos;

	philos = malloc(sizeof(t_thread_table));
	philos->n_args = collect(ac);
	philos->vector = push_back(philos->n_args, av);
	philos->optional_argument = -1;
	if (philos->n_args == (ARGUMENT_SUCCESS | OPTIONAL_TRUE))
		philos->optional_argument = philos->vector[philos->n_args - 1];
	if (!create_threads(philos))
		return (philos);
	return (NULL);
}
