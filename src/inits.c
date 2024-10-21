#include "../philo.h"

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
