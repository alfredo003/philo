#include "../philo.h"
static int	init_mutex(t_params *params)
{
	int	i;

	i = 0;
	params->death = 0;
	params->fork = 0;
	params->death = malloc(sizeof(pthread_mutex_t));
	if (!params->death)
		return (put_error("Mutex death: malloc failed\n", params, 0, 1));
	params->fork = malloc(sizeof(pthread_mutex_t) * params->n_philo);
	if (!params->fork)
		return (put_error("Mutex fork: malloc failed\n", params, 0, 1));
	if (pthread_mutex_init(params->death, NULL) != 0)
		return (put_error("init of mutex failed\n", params, 0, 1));
	while (++i <= params->n_philo)
	{
		if (pthread_mutex_init(&params->fork[i], NULL) != 0)
			return (put_error("Mutex fork failed\n", params, 0, 1));
	}
	return (0);
}

int	init_params(t_params *params, char **argv)
{
	int	mutex;

	mutex = -1;
	params->n_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->check_n_snack = 0;
	params->max_iter = 0;
	params->time_start = 0;
	params->ready = 0;
	params->end = 0;
	if (argv[5]) 
	{
		params->check_n_snack = 1;
		params->max_iter = ft_atoi(argv[5]);
		if (params->max_iter <= 0)
			return (1);
	}
	if (params->n_philo > 0)
		mutex = init_mutex(params);
	return (mutex || params->n_philo <= 0
		|| params->time_to_die <= 0 || params->time_to_eat <= 0
		|| params->time_to_sleep <= 0);
}
