/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:09:44 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/23 06:53:14 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*philosopher(void *table)
{
	t_philo	*philo;	
	philo = table;
	
	while (1)
	{
		if(get_diff(philo->last_eat_time, get_now()) > philo->time_to_sleep)
			exit(1);
		printf("%lld : %lld\n", philo->last_eat_time, get_now());
		pthread_mutex_lock(&philo->fork[min_fork(philo->lfork, philo->rfork)]);
		
		pthread_mutex_lock(&philo->table->print);
		printf("Philosopher %d : has taken a fork\n", philo->id);
		pthread_mutex_unlock(&philo->table->print);
		
		pthread_mutex_lock(&philo->fork[philo->lfork]);
		
		pthread_mutex_lock(&philo->table->print);
		printf("Philospher %d : has taken a fork\n", philo->id);
		printf("Philospher %d : is eating\n", philo->id);
		pthread_mutex_unlock(&philo->table->print);
		
		usleep(philo->time_to_eat);
		
		pthread_mutex_lock(&philo->table->print);
		pthread_mutex_unlock(&philo->table->print);
		philo->last_eat_time = get_now();
		
		pthread_mutex_unlock(&philo->fork[philo->lfork]);
		pthread_mutex_unlock(&philo->fork[philo->rfork]);
		
		pthread_mutex_lock(&philo->table->print);
		printf("Philosopher %d : is sleep\n", philo->id);
		pthread_mutex_unlock(&philo->table->print);
		
		usleep(philo->time_to_sleep);
		
		pthread_mutex_lock(&philo->table->print);
		printf("Philosopher %d : is thinking\n", philo->id);
		pthread_mutex_unlock(&philo->table->print);
	}
	return (NULL);
}

int	min_fork(int lfork, int rfork)
{
	if(lfork < rfork)
		return (lfork);
	return (rfork);
}

long long	get_now(void)
{
	struct timeval	smt;
	
	gettimeofday(&smt, NULL);
	return ((smt.tv_sec * 1000) + (smt.tv_usec / 1000));
}

long long	get_diff(long long past_time, long long present_time)
{
	return (present_time - past_time);
}