#include "../philo.h"


int	init_philo(t_params *p, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < p->num)
	{
		philo[i].id = i;
		philo[i].dead = 0;
		philo[i].iter_num = 0;
		philo[i].thread_start = 0;
		philo[i].snack = 0;
		philo[i].par = p;
		philo[i].lf = &p->fork[i];
		philo[i].rf = 0;
	}
	return (0);
}
static void check_thread(t_params *params,t_philo *philo)
{
	int i;
	
	while(!params->ready)
		
}

static int init_thread(t_params *params,t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < params->number_of_philosophers)
	{
		philo[i].rigtht_fork = philo[(i + 1) % params->number_of_philosophers].left_fork;
		if(pthread_create(&philo[i].life_thread_id, NULL, &thread_routine, &philo[i]) == -1)
			return (put_error("Error\nFeild thread!\n", params, philo, 2));
		i = -1;
		params->start = time_now();
		while(++i < params->number_of_philosophers)
		{
			philo[i].thread_start = params->start;
			philo[i].snack = params->start;
		}
		params->ready =1;
		return (0);
	}
}

int philo(t_params *params)
{
	t_philo *philo;
	
	philo = malloc(sizeof(t_philo) * params->number_of_philosophers);
	if(!philo || init_philo(params,philo))
		return (-1);
	if(init_thread(params, philo))
		return (-1);
	check_thread(params, philo);
			
	return (0);
}
