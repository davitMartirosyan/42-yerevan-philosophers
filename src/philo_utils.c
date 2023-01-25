/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:52:12 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/24 13:06:50 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_digit(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (1);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	atoint(char *num)
{
	int	i;
	int	sign;
	int	toint;

	i = 0;
	sign = 1;
	toint = 0;
	if (is_digit(num))
		return (-1);
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
	vector[0] = atoint(av[0]);
	i = 0;
	while (++i < n_args)
		vector[i] = atoint(av[i]);
	vector[i] = 0;
	return (vector);
}

int	fnd(int *vector, int quantity)
{
	int	i;

	i = -1;
	while (++i < quantity)
		if (vector[i] < 1)
			break ;
	return (i);
}

int	invalid_arguments(t_thread_table *philos)
{
	char	*invalid[5];
	int		i;

	invalid[0] = "Philosophers";
	invalid[1] = "Time_To_Die";
	invalid[2] = "Time_To_Eat";
	invalid[3] = "Time_To_Sleep";
	invalid[4] = "Must_To_Eat";
	if (philos->vector[0] < 1 || philos->vector[0] > 200)
	{
		printf("Invalid Arguments: <%s> Must in range 2 to 200\n", invalid[0]);
		return (1);
	}
	i = -1;
	while (++i < philos->n_args)
	{
		if (philos->vector[i] < 1)
		{
			printf("Invalid Arguments: count of <%s> must greather than [%d]\n", \
				invalid[i], philos->vector[i]);
			return (1);
		}
	}
	return (0);
}
