/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:56:03 by achivela          #+#    #+#             */
/*   Updated: 2024/10/23 10:56:04 by achivela         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"

void	*routine(void *task)
{
	t_philo	*philo;

	philo = (t_philo *)task;
	while (!philo->params->ready)
		continue ;
	if (philo->id & 1)
		ft_usleep(philo->params->time_to_eat * 0.9 + 1);
	/*while (!philo->params->end)
	{
		ft_eat(philo);
		ft_sleep_and_think(philo);
	}*/
	return (NULL);
}