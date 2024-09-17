#include "../philo.h"

int main(int argc,char **argv)
{
	(void)argv;
	t_params params;
	if(argc != 5 && argc != 6)
		put_error("Error: invalid arguments\n", &params, 0, 1);
	return (0);
}
