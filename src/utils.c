#include "../philo.h"

int put_error(char *s, t_params *params, t_philo *philo, int malloc)
{
	if (malloc)
	{
		if (params->death)
			free(params->death);
		if (params->fork)
			free(params->fork);
		if (philo)
			free(philo);
	}		
	return (printf("%s", s));
}

int	ft_atoi(const char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}
