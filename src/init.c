 #include "../header/philo.h"

void	init_threads(t_params *params, char **argv)
{
	params->n_philo = ft_atoi(argv[1]);
	params->time_die = ft_atoi(argv[2]);
	params->time_eat = ft_atoi(argv[3]);
	params->time_sleep = ft_atoi(argv[4]);
	params->died = 0;
	pthread_mutex_init(&params->init_mutex, NULL);
	pthread_mutex_init(&params->dead_mutex, NULL);
	pthread_mutex_init(&params->g_print_mutex, NULL);
}

void	init_philo(t_philo *philo, t_params *params, int id)
{
	philo->id = id;
	philo->par = params;
	philo->stamina = params->time_die;
	philo->t_last_meal = 0;
	if (params->ac == 6)
		philo->num_ref = ft_atoi(params->av[5]);
	else
		philo->num_ref = -1;
}

void	start_forks_mutex(t_params *params)
{
	int	i;
	int	n_philo;

	i = 0;
	n_philo = params->n_philo;
	params->eat_mutex = malloc(sizeof(pthread_mutex_t) * n_philo);
	while (i < n_philo)
	{
		pthread_mutex_init(&params->eat_mutex[i], NULL);
		i++;
	}
}

void	init_params(t_params *params, int argc, char **argv)
{
	(void)argc;
	init_threads(params, argv);
	start_forks_mutex(params);
}
