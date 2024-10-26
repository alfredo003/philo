/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:00:41 by achivela          #+#    #+#             */
/*   Updated: 2024/10/26 14:47:02 by achivela         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"

static void	print_routine_mutex(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->params->over_mtx);
	print_routine(philo, action);
	pthread_mutex_unlock(philo->params->over_mtx);
}

static void	ft_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_routine_mutex(philo, "has taken left fork");
	pthread_mutex_lock(philo->right_fork);
	print_routine_mutex(philo, "has taken right fork");
	pthread_mutex_lock(philo->params->meal_mtx);
	philo->meal = time_now();
	philo->iter_num++;
	pthread_mutex_unlock(philo->params->meal_mtx);
	print_routine_mutex(philo, "is eating");
	ft_usleep(philo->params->time_eat);
	print_routine_mutex(philo, "is sleeping");
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ft_usleep(philo->params->time_sleep);
	print_routine_mutex(philo, "is thinking");
}

void	*philo_routine(void *task)
{
	t_philo	*philo;

	philo = (t_philo *)task;
	while (!pthread_mutex_lock(philo->params->ready_mtx) && !philo->params->ready
		&& !pthread_mutex_unlock(philo->params->ready_mtx))
		usleep(50);
	pthread_mutex_unlock(philo->params->ready_mtx);
	if (philo->id & 1)
		ft_usleep(philo->params->time_eat * 0.9 + 1);
	while (!pthread_mutex_lock(philo->params->over_mtx) && !philo->params->over)
	{
		pthread_mutex_unlock(philo->params->over_mtx);
		ft_routine(philo);
	}
	pthread_mutex_unlock(philo->params->over_mtx);
	return (NULL);
}
