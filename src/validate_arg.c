 #include "../header/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_philosopher_num(int phi_num)
{
	if (phi_num > 200)
	{
		write(1, "Error: Number of philosophers exceeds 200\n", 42);
		return (1);
	}
	if (phi_num <= 0)
	{
		write(1, "Error: Number of philosophers cannot be negative\n", 50);
		return (1);
	}
	return (0);
}

int	check_limits(char **av)
{
	int	phi_num;

	phi_num = ft_atoi(av[1]);
	if (check_philosopher_num(phi_num))
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

int	validate_args(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (check_limits(av))
		return (1);
	i = 1;
	while (i < ac)
	{
		if (!check_digits(av[i]))
		{
			write(1, "Error\n", 6);
			return (1);
		}
		i++;
	}
	return (0);
}
