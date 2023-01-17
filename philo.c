/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:09:08 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 18:59:31 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char **av)
{
	int				*args;
	int				n_args;
	t_thread_table	*philos;

	(void)args;
	n_args = collect(ac);
	if (n_args == ARGUMENT_ERROR)
	{
		printf("error\n");
		return (1);
	}
	philos = create_philos_table(ac, av);
	if (philos)
		create_threads();
	else
		return (-1);
}

t_thread_table	*create_philos_table(int ac, char **av)
{
	t_thread_table	*philos;

	philos = (t_thread_table *)malloc(sizeof(t_thread_table));
	if (!philos)
		return (NULL);
	philos->n_args = collect(ac);
	philos->vector = push_back(philos->n_args, av);
	if (philos->n_args == (ARGUMENT_SUCCESS | OPTIONAL_TRUE))
		philos->optional_argument = philos->vector[philos->n_args - 1];
	else
		philos->optional_argument = -1;
	return (philos);
}