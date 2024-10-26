/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:10:59 by achivela          #+#    #+#             */
/*   Updated: 2024/10/26 13:39:49 by achivela         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"

void	end_monitor(t_params *params, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < params->n_philo && philo)
		pthread_join(philo[i].life_tid, (void *)&philo[i]);
	pthread_mutex_destroy(params->over_mtx);
	pthread_mutex_destroy(params->meal_mtx);
	pthread_mutex_destroy(params->fork);
	pthread_mutex_destroy(params->ready_mtx);
	free(params->over_mtx);
	free(params->meal_mtx);
	free(params->fork);
	free(params->ready_mtx);
	free(philo);
}

int	monitoring(t_params *params)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * params->n_philo);
	if (!philo || init_philo(params, philo))
		return (1);
	if (init_monitor(params, philo))
		return (1);
	check_monitor(params, philo);
	end_monitor(params, philo);
	return (0);
}
