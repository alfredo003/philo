/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:17:43 by achivela          #+#    #+#             */
/*   Updated: 2024/10/26 14:53:34 by achivela         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"

static int	check_meals(t_philo *philo)
{
	pthread_mutex_lock(philo->params->meal_mtx);
	if (philo->params->check_meal)
	{
		if (philo->iter_num >= philo->params->max_iter)
			++philo->params->philos_full;
		if (philo->params->philos_full == philo->params->n_philo)
			return (pthread_mutex_unlock(philo->params->meal_mtx) || 1);
	}
	pthread_mutex_unlock(philo->params->meal_mtx);
	return (0);
}

static int	someone_died(t_philo *philo)
{
	pthread_mutex_lock(philo->params->over_mtx);
	philo->dead = 1;
	print_routine(philo, "died");
	philo->params->over = 1;
	pthread_mutex_unlock(philo->params->over_mtx);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

static int	check_death(t_philo *philo)
{
	long int	now;

	pthread_mutex_lock(philo->params->meal_mtx);
	now = time_now() - philo->meal;
	pthread_mutex_unlock(philo->params->meal_mtx);
	if (now >= philo->params->time_die)
		return (someone_died(philo));
	return (0);
}

void	check_monitor(t_params *params, t_philo *philo)
{
	int	i;

	while (!params->over)
	{
		i = -1;
		params->philos_full = 0;
		while (++i < params->n_philo)
		{
			if (check_death(&philo[i]) || check_meals(&philo[i]))
			{
				pthread_mutex_lock(params->over_mtx);
				params->over = 1;
				pthread_mutex_unlock(params->over_mtx);
			}
		}
		usleep(30);
	}
	if (params->check_meal && !pthread_mutex_lock(philo->params->meal_mtx) && \
	philo[params->n_philo - 1].iter_num >= params->max_iter)
	{
		ft_usleep(100);
		printf("\n\tAll philosophers have eaten %d times\n", params->max_iter);
		pthread_mutex_unlock(philo->params->meal_mtx);
		return;
	}
	pthread_mutex_unlock(philo->params->meal_mtx);
	return ;
}
