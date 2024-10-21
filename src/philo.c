#include "../philo.h"


int	philos(t_params *params)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * params->n_philo);
	if (!philo || init_philo(params, philo) || init_thread(params, philo))
		return (1); 
	//check_thread(params, philo);
	//end_thread(params, philo);
	return (0);
}