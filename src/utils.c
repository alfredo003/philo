/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:49:32 by achivela          #+#    #+#             */
/*   Updated: 2024/09/19 11:49:48 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	put_error(char *s, t_params *par, t_philo *p, int malloc)
{
	if (malloc)
	{
		if (par->death)
			free(par->death);
		if (par->fork)
			free(par->fork);
		if (p)
			free(p);
	}		
	printf("%s", s);
	return (1);
}

void print_logs(t_philo *philo,char *action)
{
	pthread_mutex_lock(philo->par->death);
	if(philo->par->end)
	{
		pthread_mutex_unlock(philo->par->death);
		return ;
	}
	printf("%ldms %d %s\n", time_now() - philo->thread_start, philo->id, action);
	pthread_mutex_unlock(philo->par->death);
}

long int	time_now(void)
{
	struct timeval	now;
	long int milliseconds;

	gettimeofday(&now, NULL);
	milliseconds = (now.tv_sec * 1000) + (now.tv_usec / 1000);

	return milliseconds;
}

int ft_usleep(long int time)
{
	long int start_time;
	
	start_time = time_now();
	while ((time_now() - start_time) < time)
		usleep(150);
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	unsigned long long int	n;

	i = 0;
	n = 0;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i++] - '0');
	}

	return (sign * (int)n);
}
