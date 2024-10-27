/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:53:43 by achivela          #+#    #+#             */
/*   Updated: 2024/10/27 12:41:41 by achivela         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"

int	init_philo(t_params *params, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < params->n_philo)
	{
		philo[i].id = i;
		philo[i].dead = 0;
		philo[i].iter_num = 0;
		philo[i].monitor_start = 0;
		philo[i].meal = 0;
		philo[i].params = params;
		philo[i].left_fork = &params->fork[i];
		philo[i].right_fork = 0;
	}
	return (0);
}

static int	mutex_alloc(t_params *params)
{
	params->meal_mtx = malloc(sizeof(pthread_mutex_t));
	if (!params->meal_mtx)
		return (put_msg("Mutex meal: malloc failed\n", params, 0, 1));
	params->ready_mtx = malloc(sizeof(pthread_mutex_t));
	if (!params->ready_mtx)
		return (put_msg("Mutex ready: malloc failed\n", params, 0, 1));
	params->over_mtx = malloc(sizeof(pthread_mutex_t));
	if (!params->over_mtx)
		return (put_msg("Mutex over: malloc failed\n", params, 0, 1));
	params->fork = malloc(sizeof(pthread_mutex_t) * params->n_philo);
	if (!params->fork)
		return (put_msg("Mutex fork: malloc failed\n", params, 0, 1));
	return (0);
}

static int	init_mutex(t_params *params)
{
	int	i;

	params->over_mtx = 0;
	params->fork = 0;
	if (mutex_alloc(params))
		return (1);
	if (pthread_mutex_init(params->meal_mtx, NULL) == -1)
		return (put_msg("Mutex meal failed\n", params, 0, 1));
	if (pthread_mutex_init(params->over_mtx, NULL) == -1)
		return (put_msg("Mutex init failed\n", params, 0, 1));
	i = -1;
	if (pthread_mutex_init(params->ready_mtx, NULL) == -1)
		return (put_msg("Mutex init failed\n", params, 0, 1));
	i = -1;
	while (++i < params->n_philo)
		if (pthread_mutex_init(&params->fork[i], NULL) == -1)
			return (put_msg("Mutex init failed\n", params, 0, 1));
	return (0);
}

int	init_params(t_params *params, int argc, char **argv)
{
	int	mutex;

	mutex = -1;
	params->n_philo = ft_atoi(argv[1]);
	params->time_die = ft_atoi(argv[2]);
	params->time_eat = ft_atoi(argv[3]);
	params->time_sleep = ft_atoi(argv[4]);
	params->max_iter = -2;
	params->check_meal = 0;
	params->philos_full = 0;
	params->start = 0;
	params->ready = 0;
	if (argc == 6)
	{
		params->check_meal = 1;
		params->max_iter = ft_atoi(argv[5]);
		if (params->max_iter < 1)
			params->max_iter = 0;
	}
	params->over = 0;
	if (params->n_philo > 0)
		mutex = init_mutex(params);
	return (mutex || params->n_philo <= 0
		|| params->time_die <= 0 || params->time_die <= 0
		|| params->time_sleep <= 0 || params->max_iter == 0);
}

int	init_monitor(t_params *params, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < params->n_philo)
	{
		philo[i].right_fork = philo[(i + 1) % params->n_philo].left_fork;
		if (pthread_create(&philo[i].life_tid, NULL, &philo_routine,
				&philo[i]) == -1)
			return (put_msg("fail createing thread\n", params, philo, 2));
	}
	i = -1;
	params->start = time_now();
	while (++i < params->n_philo)
	{
		philo[i].monitor_start = params->start;
		pthread_mutex_lock(params->meal_mtx);
		philo[i].meal = params->start;
		pthread_mutex_unlock(params->meal_mtx);
	}
	pthread_mutex_lock(params->ready_mtx);
	params->ready = 1;
	pthread_mutex_unlock(params->ready_mtx);
	return (0);
}
