#include "../philo.h"

int	put_msg(char *s, t_params *par, t_philo *philo, int malloc)
{
	if (malloc)
	{
		if (par->meal_mtx)
			free(par->meal_mtx);
		if (par->over_mtx)
			free(par->over_mtx);
		if (par->fork)
			free(par->fork);
		if (par->ready_mtx)
			free(par->ready_mtx);
		if (philo)
			free(philo);
	}
	return (printf("%s", s));
}

void	print_routine(t_philo *philo, char *action)
{
	if (philo->par->over == 1)
		return ;
	printf("%ld ms %d %s\n", time_now() - philo->monitor_start, philo->id + 1,
		action);
}

// When all philos
void	final_print(int alive)
{
	printf("\t/-=-=-=-=-=-=-=-=-=\\\n");
	if (alive)
		printf("\t|  I'M LOVIN' IT®  |\t🍔🍟\n");
	else
		printf("\t|     YOU DIED     |\t💀\n");
	printf("\t\\=-=-=-=-=-=-=-=-=-/\n");
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	--i;
	while (str[++i] >= '0' && str[i] <= '9')
		res = (res * 10) + str[i] - '0';
	return (res * sign);
}
long int	time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec * 0.001));
}

int	ft_usleep(long int time)
{
	long int	start_time;

	start_time = time_now();
	while ((time_now() - start_time) < time)
		usleep(100);
	return (1);
}
