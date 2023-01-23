/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:09:08 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/23 15:45:35 by dmartiro         ###   ########.fr       */
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
	if (table)
		init(table);
	return (-1);
}
//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