#include "../philo.h"

void	*routine(void *task)
{
	t_philo	*philo;

	philo = (t_philo *)task;
	while (!philo->params->ready)
		continue ;
	if (philo->id & 1)
		ft_usleep(philo->params->time_to_eat * 0.9 + 1);
	while (!philo->params->end)
	{
		ft_eat(philo);
		ft_sleep_and_think(philo);
	}
	return (NULL);
}