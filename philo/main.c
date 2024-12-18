/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:35:29 by achivela          #+#    #+#             */
/*   Updated: 2024/10/30 12:36:01 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_for_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->par->init_mutex);
	gettimeofday(&philo->time_born, NULL);
	pthread_mutex_unlock(&philo->par->init_mutex);
	if (philo->id % 2 == 0)
		ft_usleep(philo, 10);
	return (1);
}

void	case_one_philo(t_philo *philo)
{
	gettimeofday(&philo->time_born, NULL);
	ft_usleep(philo, philo->par->time_die);
	printf("%d %d has taken a fork\n",
		0, philo->id);
	printf("%d %d \033[0;31mdied\033[0m\n",
		get_elapsed_time(philo->time_born), philo->id);
}

void	*ft_routine(void *arg)
{
	t_philo		philo;

	philo = *(t_philo *)arg;
	if (philo.par->n_philo == 1)
	{
		case_one_philo(&philo);
		return (NULL);
	}
	else
		wait_for_start(&philo);
	while (philo.num_ref != 0)
	{
		if (ft_die(&philo))
			break ;
		check_forks(&philo);
		ft_printf_status(&philo, 's');
		if (ft_die(&philo))
			break ;
		ft_usleep(&philo, philo.par->time_sleep);
		ft_printf_status(&philo, 't');
		if (ft_die(&philo))
			break ;
	}
	return (NULL);
}

int	destroy_my_mutex(t_params *params)
{
	int	i;

	i = 0;
	while (i < params->n_philo)
	{
		pthread_mutex_destroy(&params->eat_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&params->init_mutex);
	pthread_mutex_destroy(&params->dead_mutex);
	pthread_mutex_destroy(&params->g_print_mutex);
	free(params->eat_mutex);
	return (0);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_philo		*philo;
	int			i;

	i = 0;
	if (check_args(argc, argv))
		return (1);
	init_params(&params, argc, argv);
	params.threads = (pthread_t *)malloc(sizeof(pthread_t) * params.n_philo);
	philo = (t_philo *)malloc(sizeof(t_philo) * params.n_philo);
	while (i < params.n_philo)
	{
		init_philo(&philo[i], &params, i + 1);
		pthread_create(&params.threads[i], NULL, &ft_routine, &philo[i]);
		usleep(50);
		i++;
	}
	i = 0;
	while (i < params.n_philo)
		pthread_join(params.threads[i++], NULL);
	free(philo);
	destroy_my_mutex(&params);
	free(params.threads);
}
