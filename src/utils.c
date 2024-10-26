/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:48:39 by achivela          #+#    #+#             */
/*   Updated: 2024/10/26 14:50:45 by achivela         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"

int	put_msg(char *s, t_params *params, t_philo *philo, int malloc)
{
	if (malloc)
	{
		if (params->meal_mtx)
			free(params->meal_mtx);
		if (params->over_mtx)
			free(params->over_mtx);
		if (params->fork)
			free(params->fork);
		if (params->ready_mtx)
			free(params->ready_mtx);
		if (philo)
			free(philo);
	}
	return (printf("%s", s));
}

void	print_routine(t_philo *philo, char *action)
{
	if (philo->params->over == 1)
		return ;
	printf("%ld ms %d %s\n", time_now() - philo->monitor_start, philo->id + 1,
		action);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	--i;
	while (str[++i] >= '0' && str[i] <= '9')
		res = (res * 10) + str[i] - '0';
	return (res * sign);
}

long int	time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec * 0.001));
}

int	ft_usleep(long int time)
{
	long int	start_time;

	start_time = time_now();
	while ((time_now() - start_time) < time)
		usleep(100);
	return (1);
}
