 #include "../header/philo.h"

void	init_th(t_th *th, char **av)
{
	th->num_ph = ft_atoi(av[1]);
	th->t_die = ft_atoi(av[2]);
	th->t_eat = ft_atoi(av[3]);
	th->t_sleep = ft_atoi(av[4]);
	th->died = 0;
	pthread_mutex_init(&th->init_mutex, NULL);
	pthread_mutex_init(&th->dead_mutex, NULL);
	pthread_mutex_init(&th->g_print_mutex, NULL);
}

void	init_ph(t_ph *ph, t_th *th, int id)
{
	ph->id = id;
	ph->th = th;
	ph->stamina = th->t_die;
	ph->t_last_meal = 0;
	if (th->ac == 6)
		ph->num_ref = ft_atoi(th->av[5]);
	else
		ph->num_ref = -1;
}

void	start_forks_mutex(t_th *th)
{
	int	i;
	int	n_ph;

	i = 0;
	n_ph = th->num_ph;
	th->eat_mutex = malloc(sizeof(pthread_mutex_t) * n_ph);
	while (i < n_ph)
	{
		pthread_mutex_init(&th->eat_mutex[i], NULL);
		i++;
	}
}

void	start_structs(t_th *th, int ac, char **av)
{
	(void)ac;
	init_th(th, av);
	start_forks_mutex(th);
}
