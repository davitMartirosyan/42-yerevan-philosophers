/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:52:12 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/18 17:17:59 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int	atoint(char *num)
{
	int	i;
	int	sign;
	int	toint;

	i = 0;
	sign = 1;
	toint = 0;
	while (num[i] == 32 || (num[i] > 10 && num[i] < 14))
		i++;
	if (num[i] == '-' || num[i] == '+')
	{
		if (num[i] == '-')
			sign = -1;
		i++;
	}
	while (num[i] >= '0' && num[i] <= '9')
		toint = toint * 10 + num[i++] - '0';
	toint *= sign;
	return (toint);
}

int	*push_back(int n_args, char **av)
{
	int	*vector;
	int	i;

	(void)av;
	(void)*(av++);
	vector = malloc(sizeof(int) * (n_args + 1));
	if (!vector)
		return (NULL);
	i = -1;
	while (++i < n_args)
		vector[i] = atoint(av[i]);
	vector[i] = 0;
	return (vector);
}
