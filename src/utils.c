#include "../philo.h"

void	put_error(char *s, t_params *par, t_philo *p, int malloc)
{
	if (malloc)
	{
		if (par->death)
			free(par->death);
		if (par->fork)
			free(par->fork);
		if (p)
			free(p);
	}		
	printf("%s", s);
	exit(1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	unsigned long long int	n;

	i = 0;
	n = 0;
	sign = 1;

	if (str[i] == '-' || str[i] == '+')
		sign = (str[i++] == '-') ? -1 : 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (n > LONG_MAX / 10 || (n == LONG_MAX / 10 && (str[i] - '0') > LONG_MAX % 10))
			return (sign == 1 ? -1 : 0);
		n = n * 10 + (str[i++] - '0');
	}

	return (sign * (int)n);
}

