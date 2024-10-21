#include "../philo.h"
int	main(int argc, char **argv) 
{
	t_params	params;

	if (argc == 5 || argc == 6)
	{
		if (init_params(&params, argv))
			return (put_error("Error: invalid arguments\n", &params, 0, 1));
		if (philos(&params))
			put_error("finish!\n", &params, 0, 1);
	}else
		put_error("./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]\n", &params, 0, 0);
	return (0);
}
