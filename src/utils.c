 #include "../header/philo.h"

int	get_elapsed_time_ms(struct timeval ta)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return ((tm.tv_sec * 1000 + tm.tv_usec / 1000)
		- (ta.tv_sec * 1000 + ta.tv_usec / 1000));
}

void	ft_usleep(t_philo *philo, int time)
{
	struct timeval	before;
	struct timeval	end;
	long			elapsed_time;

	gettimeofday(&before, NULL);
	while (1)
	{
		gettimeofday(&end, NULL);
		elapsed_time = (end.tv_sec * 1000 + end.tv_usec / 1000)
			- (before.tv_sec * 1000 + before.tv_usec / 1000);
		if (elapsed_time >= time || ft_die(philo))
			break ;
		usleep(100);
	}
}

int	ft_result(int k, const char *str, int i)
{
	int	a;

	a = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = (a * 10) + (str[i] - '0');
		i++;
	}
	if (k == 1)
		a = a * -1;
	return (a);
}

int	ft_atoi(const char *str)
{
	intptr_t	a;
	int			i;
	int			k;

	a = 0;
	i = 0;
	k = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			k++;
		i++;
	}
	if (str[i] >= '0' && str[i] <= '9')
		return (ft_result(k, str, i));
	return (a);
}
