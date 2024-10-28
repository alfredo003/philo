 #include "../header/philo.h"

int	ft_wait_for_start(t_ph *ph)
{
	pthread_mutex_lock(&ph->th->init_mutex);
	gettimeofday(&ph->t_born, NULL);
	pthread_mutex_unlock(&ph->th->init_mutex);
	if (ph->id % 2 == 0)
		ft_usleep(ph, 10);
	return (1);
}

void	caseof1(t_ph *ph)
{
	gettimeofday(&ph->t_born, NULL);
	ft_usleep(ph, ph->th->t_die);
	printf("%d %d died\n", get_elapsed_time_ms(ph->t_born), ph->id);
}

void	*ft_routine(void *arg)
{
	t_ph		ph;

	ph = *(t_ph *)arg;
	if (ph.th->num_ph == 1)
	{
		caseof1(&ph);
		return (NULL);
	}
	else
		ft_wait_for_start(&ph);
	while (ph.num_ref != 0)
	{
		if (ft_die(&ph))
			break ;
		check_forks(&ph);
		ft_printf_status(&ph, 's');
		if (ft_die(&ph))
			break ;
		ft_usleep(&ph, ph.th->t_sleep);
		ft_printf_status(&ph, 't');
		if (ft_die(&ph))
			break ;
	}
	return (NULL);
}

int	destroy_my_mutex(t_th *th)
{
	int	i;

	i = 0;
	while (i < th->num_ph)
	{
		pthread_mutex_destroy(&th->eat_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&th->init_mutex);
	pthread_mutex_destroy(&th->dead_mutex);
	pthread_mutex_destroy(&th->g_print_mutex);
	free(th->eat_mutex);
	return (0);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_philo	*philo;
	int	i;

	i = 0;
	if (check_args(argc, argv))
		return (1);
	start_structs(&params, argc, argv);
	params.ac = argc;
	params.av = argv;
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
