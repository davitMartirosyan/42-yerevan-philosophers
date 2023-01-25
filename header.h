/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:12:31 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/25 17:31:17 by dmartiro         ###   ########.fr       */
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
long long		get_now(void);
int				*push_back(int n_args, char **av);
int				is_digit(char *s);
int				atoint(char *num);
int				invalid_arguments(t_thread_table *philos);
int				create_threads(t_thread_table *thread);
int				init_mutexes(t_thread_table *philos);
int				collect(int ac);
int				fnd(int *vector, int quantity);
int				min_fork(int lfork, int rfork);
int				max_fork(int lfork, int rfork);
int				check_threads(t_thread_table *table);
int				check_all_ate(t_thread_table *table);
void			init(t_thread_table *table);
void			*philosopher(void *threads_table);
void			print(t_philo *philo, char *action);
void			is_eating(t_philo *philo);
void			__exit(t_thread_table *table);
void			__usleep(int ms);

typedef struct s_philo
{
	int				id;
	int				lfork;
	int				rfork;
	int				died;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_of_eating;
	int				counter;
	long long		starttime;
	long long		last_eat_time;
	pthread_t		thread_id;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
}	t_philo;

typedef struct s_thread_table
{
	int				n_args;
	int				optional_argument;
	int				*vector;
	char			*argument_names[5];
	int				died;
	t_philo			philos[255];
	pthread_mutex_t	forks[255];
	pthread_mutex_t	print;
}	t_thread_table;
#endif