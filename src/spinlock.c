/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spinlock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:19:36 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/24 14:01:50 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
