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

int	main(int ac, char **av)
{
	t_th	th;
	t_ph	*ph;
	int		i;

	i = 0;
	if (validate_args(ac, av))
		return (1);
	start_structs(&th, ac, av);
	th.ac = ac;
	th.av = av;
	th.th = (pthread_t *)malloc(sizeof(pthread_t) * th.num_ph);
	ph = (t_ph *)malloc(sizeof(t_ph) * th.num_ph);
	while (i < th.num_ph)
	{
		init_ph(&ph[i], &th, i + 1);
		pthread_create(&th.th[i], NULL, &ft_routine, &ph[i]);
		usleep(50);
		i++;
	}
	i = 0;
	while (i < th.num_ph)
		pthread_join(th.th[i++], NULL);
	free(ph);
	destroy_my_mutex(&th);
	free(th.th);
}
