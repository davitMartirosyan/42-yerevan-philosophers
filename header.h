/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:12:31 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/19 16:23:12 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define OPTIONAL_TRUE		0x05
# define ARGUMENT_SUCCESS	0x04
# define ARGUMENT_ERROR		0x0A

typedef struct s_thread_table	t_thread_table;
typedef struct s_philo			t_philo;

t_thread_table	*create_philos_table(int ac, char **av);
int				create_threads(t_thread_table *thread);
int				*push_back(int n_args, char **av);
int				collect(int ac);
int				atoint(char *num);
void			init(t_thread_table *table);
void			*philosopher(void *threads_table);

typedef struct s_philo
{
	int				id;
	int				lfork;
	int				rfork;
	int				iseating;
	int				issleeping;
	int				isthinking;
	int				wasdied;
	pthread_t		thread_id;
	t_thread_table	*thread_table;
}	t_philo;

typedef struct s_thread_table
{
	int				n_args;
	int				optional_argument;
	int				*vector;
	t_philo			philos[255];
	pthread_mutex_t	forks[255];
	pthread_mutex_t	mutex_eat;
}	t_thread_table;
#endif