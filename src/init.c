/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:53:43 by achivela          #+#    #+#             */
/*   Updated: 2024/10/25 18:01:48 by achivela         ###   ########.fr       */
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
		philo[i].left_fork = &par->fork[i];
		philo[i].right_fork = 0;
	}
	return (0);
}

static int	mutex_alloc(t_params *params)
{
	params->meal_mtx = malloc(sizeof(pthread_mutex_t));
	if (!par->meal_mtx)
		return (put_msg("Mutex meal: malloc failed\n", params, 0, 1));
	params->ready_mtx = malloc(sizeof(pthread_mutex_t));
	if (!par->ready_mtx)
		return (put_msg("Mutex ready: malloc failed\n", params, 0, 1));
	params->over_mtx = malloc(sizeof(pthread_mutex_t));
	if (!par->over_mtx)
		return (put_msg("Mutex over: malloc failed\n", params, 0, 1));
	params->fork = malloc(sizeof(pthread_mutex_t) * par->num);
	if (!params->fork)
		return (put_msg("Mutex fork: malloc failed\n", params, 0, 1));
	return (0);
}

static int	init_mutex(t_params *params)
{
	int	i;

	par->over_mtx = 0;
	par->fork = 0;
	if (mutex_alloc(params))
		return (1);
	if (pthread_mutex_init(params->meal_mtx, NULL) == -1)
		return (put_msg("Mutex meal failed\n", params, 0, 1));
	if (pthread_mutex_init(params->over_mtx, NULL) == -1)
		return (put_msg("Mutex init failed\n", params, 0, 1));
	i = -1;
	if (pthread_mutex_init(params->ready_mtx, NULL) == -1)
		return (put_msg("Error\nMutex init failed\n", params, 0, 1));
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
		|| params->time_sleep <= 0 || par->max_iter == 0);
}

int	init_monitor(t_params *par, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < par->num)
	{
		philo[i].rf = philo[(i + 1) % par->num].lf;
		if (pthread_create(&philo[i].life_tid, NULL, &philo_routine,
				&philo[i]) == -1)
			return (put_msg("Error\nFail createing thread\n", par, philo, 2));
	}
	i = -1;
	par->start = time_now();
	while (++i < par->num)
	{
		philo[i].monitor_start = par->start;
		pthread_mutex_lock(par->meal_mtx);
		philo[i].meal = par->start;
		pthread_mutex_unlock(par->meal_mtx);
	}
	pthread_mutex_lock(par->ready_mtx);
	par->ready = 1;
	pthread_mutex_unlock(par->ready_mtx);
	return (0);
}
