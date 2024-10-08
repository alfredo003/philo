/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:49:31 by achivela          #+#    #+#             */
/*   Updated: 2024/10/07 13:49:33 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	check_snacks(t_philo params, int last)
{
	if (params.par->check_n_snack && last
		== params.par->number_of_philosophers -1 && params.par->max_iter)
		return (ft_usleep(300));
	return (0);
}

static void	check_thread(t_params *params, t_philo *philo)
{
	int	i;

	i = 0;
	while (!params->ready)
		continue ;
	while (!params->end)
	{
		i = -1;
		while (++i < params->number_of_philosophers)
			if (check_death(&philo[i]) || check_snacks(philo[i], i))
				params->end = 1;
	}
	if (params->check_n_snack && philo[params->number_of_philosophers
			-1].iter_num == params->max_iter)
	{
		ft_usleep(5 * params->number_of_philosophers);
		printf("All philosophers have eaten - %d - times\n", params->max_iter);
		return ;
	}
	return ;
}

static int	init_thread(t_params *params, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < params->number_of_philosophers)
	{
		philo[i].right_fork = philo[(i + 1)
			% params->number_of_philosophers].left_fork;
		if (pthread_create(&philo[i].life_tid, NULL, &routine, &philo[i]) == -1)
			return (put_error("Error\nFeild thread!\n", params, philo, 1));
	}
	i = -1;
	params->start = time_now();
	while (++i < params->number_of_philosophers)
	{
		philo[i].thread_start = params->start;
		philo[i].snack = params->start;
	}
	params->ready = 1;
	return (0);
}

static void	end_thread(t_params *params, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < params->number_of_philosophers)
		pthread_join(philo[i].life_tid, (void *)&philo[i]);
	pthread_mutex_destroy(params->death);
	pthread_mutex_destroy(params->fork);
	free(params->death);
	free(params->fork);
	free(philo);
}

int	philos(t_params *params)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * params->number_of_philosophers);
	if (!philo || init_philo(params, philo))
		return (1);
	if (init_thread(params, philo))
		return (1);
	check_thread(params, philo);
	end_thread(params, philo);
	return (0);
}
