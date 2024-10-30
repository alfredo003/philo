/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:40:34 by achivela          #+#    #+#             */
/*   Updated: 2024/10/30 14:40:43 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/philo.h"

void	ft_eat(t_philo *philo)
{
	ft_printf_status(philo, 'e');
	ft_usleep(philo, philo->par->time_eat);
	philo->time_last_meal = get_elapsed_time(philo->time_born);
	if (philo->num_ref > 0)
		philo->num_ref--;
}

void	check_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = (philo->id - 1 + philo->par->n_philo) % philo->par->n_philo;
	right_fork = philo->id % philo->par->n_philo;
	ft_die(philo);
	if (left_fork < right_fork)
	{
		pthread_mutex_lock(&philo->par->eat_mutex[left_fork]);
		pthread_mutex_lock(&philo->par->eat_mutex[right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->par->eat_mutex[right_fork]);
		pthread_mutex_lock(&philo->par->eat_mutex[left_fork]);
	}
	ft_printf_status(philo, 'f');
	ft_printf_status(philo, 'f');
	ft_die(philo);
	ft_eat(philo);
	pthread_mutex_unlock(&philo->par->eat_mutex[left_fork]);
	pthread_mutex_unlock(&philo->par->eat_mutex[right_fork]);
	ft_die(philo);
}

int	ft_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->par->dead_mutex);
	if (philo->par->died == 1 || philo->num_ref == 0)
	{
		pthread_mutex_unlock(&philo->par->dead_mutex);
		return (1);
	}
	if (philo->stamina < get_elapsed_time(philo->time_born)
		- philo->time_last_meal && !philo->par->died)
	{
		ft_printf_status(philo, 'd');
		philo->par->died = 1;
	}
	pthread_mutex_unlock(&philo->par->dead_mutex);
	return (0);
}

char	*ft_status(char c)
{
	char	*str;

	if (c == 'e')
		str = "\033[32mis eating\033[0m\n";
	else if (c == 'f')
		str = "has taken a fork\n";
	else if (c == 's')
		str = "is sleeping\n";
	else if (c == 't')
		str = "is thinking\n";
	else
		str = "\033[0;31mdied\033[0m\n";
	return (str);
}

void	ft_printf_status(t_philo *philo, char c)
{
	char	*str;
	int		elapsed_time;

	elapsed_time = get_elapsed_time(philo->time_born);
	str = ft_status(c);
	pthread_mutex_lock(&philo->par->g_print_mutex);
	if (!philo->par->died && philo->num_ref != 0)
		printf("%d %d %s", elapsed_time, philo->id, str);
	pthread_mutex_unlock(&philo->par->g_print_mutex);
}
