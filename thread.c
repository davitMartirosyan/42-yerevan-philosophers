/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:09:44 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/23 19:03:39 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*philosopher(void *table)
{
	t_philo			*philo;
	struct timeval	smt;

	philo = table;
	if ((philo->id % 2) != 0)
		__usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->fork[min_fork(philo->lfork, philo->rfork)]);
		print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork[philo->lfork]);
		print(philo, "has taken a fork");
		is_eating(philo);
		pthread_mutex_unlock(&philo->fork[philo->lfork]);
		pthread_mutex_unlock(&philo->fork[philo->rfork]);
		print(philo, "is sleep");
		__usleep(philo->time_to_sleep);
		print(philo, "is thinking");
	}
	return (NULL);
}

void	is_eating(t_philo *philo)
{
	print(philo, "is eating");
	__usleep(philo->time_to_eat);
	if (philo->count_of_eating != -1 && philo->counter != philo->count_of_eating)
		philo->counter++;
	philo->last_eat_time = get_now();
}

int	min_fork(int lfork, int rfork)
{
	if (lfork < rfork)
		return (lfork);
	return (rfork);
}

int	max_fork(int lfork, int rfork)
{
	if (lfork > rfork)
		return (lfork);
	return (rfork);
}

long long	get_now(void)
{
	struct timeval	smt;

	gettimeofday(&smt, NULL);
	return ((smt.tv_sec * 1000) + (smt.tv_usec / 1000));
}

void	print(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->print);
	printf("[%lld] Philosopher %d : %s\n", get_now() - philo->starttime, philo->id, action);
	pthread_mutex_unlock(philo->print);
}

void	__usleep(int ms)
{
	long long	_sleep;

	_sleep = get_now();
	while((get_now() - _sleep) < ms )
		;
}