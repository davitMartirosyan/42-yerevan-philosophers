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
	// printf("%ld | %lld | %d\n", smt.tv_usec, philo->last_eat_time, philo->time_to_die);
	while (1)
	{
		gettimeofday(&smt, NULL);
		if ((smt.tv_usec - philo->last_eat_time) > philo->time_to_die)
			exit(1);
		pthread_mutex_lock(&philo->fork[min_fork(philo->lfork, philo->rfork)]);
		print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork[philo->lfork]);
		print(philo, "has taken a fork");
		print(philo, "is eating");
		usleep(philo->time_to_eat);
		gettimeofday(&smt, NULL);
		philo->last_eat_time = smt.tv_usec;
		pthread_mutex_unlock(&philo->fork[philo->lfork]);
		pthread_mutex_unlock(&philo->fork[philo->rfork]);
		print(philo, "is sleep");
		usleep(philo->time_to_sleep);
		print(philo, "is thinking");
	}
	return (NULL);
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
	return (smt.tv_usec);
}

long long	get_diff(long long past_time, long long present_time)
{
	return (present_time - past_time);
}

void	print(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->print);
	printf("Philosopher %d : %s\n", philo->id, action);
	pthread_mutex_unlock(philo->print);
}