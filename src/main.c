#include "../philo.h"


static int start_params(t_params *params,char **argv)
{
	int mutex;
	
	mutex =-1;
	params->number_of_philosophers = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->check_n_snack = 0;
	params->max_iter =-1;
	params->start = 0;
	params->ready =0;
	params->end =0;
	if(argv[5])
	{
		params->check_n_snack =1;
		params->max_iter = ft_atoi(argv[5]);
		if(params->max_iter <=0)
			return(1);
	}
	
	if(params->number_of_philosophers > 0)
		mutex = 0;
	return (mutex || params->number_of_philosophers <= 0 || params->time_to_die <= 0 || 
	params->time_to_eat <= 0 || params->time_to_sleep <= 0 || params->max_iter == 0);
	
}
int main(int argc,char **argv)
{
	t_params params;
	if((argc != 5 && argc != 6) || start_params(&params,argv))
		put_error("Error: invalid arguments\n", &params, 0, 1);
	return (0);
}
