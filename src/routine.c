 #include "../header/philo.h"

void	ft_eat(t_ph *ph)
{
	ft_printf_status(ph, 'e');
	ft_usleep(ph, ph->th->t_eat);
	ph->t_last_meal = get_elapsed_time_ms(ph->t_born);
	if (ph->num_ref > 0)
		ph->num_ref--;
}

void	check_forks(t_ph *ph)
{
	int	left_fork;
	int	right_fork;

	left_fork = (ph->id - 1 + ph->th->num_ph) % ph->th->num_ph;
	right_fork = ph->id % ph->th->num_ph;
	ft_die(ph);
	if (left_fork < right_fork)
	{
		pthread_mutex_lock(&ph->th->eat_mutex[left_fork]);
		pthread_mutex_lock(&ph->th->eat_mutex[right_fork]);
	}
	else
	{
		pthread_mutex_lock(&ph->th->eat_mutex[right_fork]);
		pthread_mutex_lock(&ph->th->eat_mutex[left_fork]);
	}
	ft_printf_status(ph, 'f');
	ft_printf_status(ph, 'f');
	ft_die(ph);
	ft_eat(ph);
	pthread_mutex_unlock(&ph->th->eat_mutex[left_fork]);
	pthread_mutex_unlock(&ph->th->eat_mutex[right_fork]);
	ft_die(ph);
}

int	ft_die(t_ph *ph)
{
	pthread_mutex_lock(&ph->th->dead_mutex);
	if (ph->th->died == 1 || ph->num_ref == 0)
	{
		pthread_mutex_unlock(&ph->th->dead_mutex);
		return (1);
	}
	if (ph->stamina < get_elapsed_time_ms(ph->t_born) - ph->t_last_meal
		&& !ph->th->died)
	{
		ft_printf_status(ph, 'd');
		ph->th->died = 1;
	}
	pthread_mutex_unlock(&ph->th->dead_mutex);
	return (0);
}

char	*ft_status_conversion(char c)
{
	char	*str;

	if (c == 'e')
		str = "\033[32mis eating\033[0m\n";
	else if (c == 'f')
		str = "has taken a fork\n";
	else if (c == 's')
		str = "is sleeping\n";
	else if (c == 't')
		str = "is thinking\n";
	else
		str = "died\n";
	return (str);
}

void	ft_printf_status(t_ph *ph, char c)
{
	char	*str;
	int		elapsed_time;

	elapsed_time = get_elapsed_time_ms(ph->t_born);
	str = ft_status_conversion(c);
	pthread_mutex_lock(&ph->th->g_print_mutex);
	if (!ph->th->died && ph->num_ref != 0)
		printf("%d %d %s", elapsed_time, ph->id, str);
	pthread_mutex_unlock(&ph->th->g_print_mutex);
}
