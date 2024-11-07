/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:05:17 by achivela          #+#    #+#             */
/*   Updated: 2024/10/30 15:05:23 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_elapsed_time(struct timeval ta)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000 + now.tv_usec / 1000)
		- (ta.tv_sec * 1000 + ta.tv_usec / 1000));
}

void	ft_usleep(t_philo *philo, int time)
{
	struct timeval	before;
	struct timeval	end;
	long			elapsed_time;

	gettimeofday(&before, NULL);
	while (1)
	{
		gettimeofday(&end, NULL);
		elapsed_time = (end.tv_sec * 1000 + end.tv_usec / 1000)
			- (before.tv_sec * 1000 + before.tv_usec / 1000);
		if (elapsed_time >= time || ft_die(philo))
			break ;
		usleep(100);
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f'
		|| str[i] == '\v' || str[i] == '\n' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		neg = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	if (neg == 1)
		return (-res);
	else
		return (res);
}
