 #include "../header/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_philo_number(int n_philo)
{
	if (n_philo > 200)
	{
		write(1, "Number of philosophers exceeds 200\n", 42);
		return (1);
	}
	if (n_philo <= 0)
	{
		write(1, "\033[0;41mError\033[0m\n", 50);
		return (1);
	}
	return (0);
}

int	check_limits(char **argv)
{
	int	n_philo;

	n_philo = ft_atoi(av[1]);
	if (check_philo_number(n_philo))
		return (1);
	return (0);
}

int	check_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		write(1, "./philo [n_philo] [time_die][time_eat] [time_sleep]\n", 6);
		return (1);
	}
	if (check_limits(argv))
		return (1);
	i = 1;
	while (i < argc)
	{
		if (!check_digits(argv[i]))
		{
			write(1, "\033[0;41mError\033[0m\n", 50);
			return (1);
		}
		i++;
	}
	return (0);
}
