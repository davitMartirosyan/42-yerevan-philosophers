/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:09:44 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/18 15:08:59 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*philosopher(void *threads_table)
{
	t_philo	*philo;

	philo = threads_table;
	usleep(200);
	printf("Philosopher %d, started to eat\n", philo->id);
	usleep(200);
	printf("Philosopher %d, started to sleep\n", philo->id);
	return (NULL);
}
