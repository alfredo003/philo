#include "../philo.h"



int someone_died(t_philo *philo)
{
	print_logs(philo, "die");
	philo->par->end = 1;
	philo->dead = 1;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

int check_death(t_philo *philo)
{
	long int now;
	
	pthread_mutex_lock(philo->par->death);
	now = time_now() - philo->snack;
	if(now >= philo->par->time_to_die)
	{
		pthread_mutex_unlock(philo->par->death);
		return (someone_died(philo));
	}
	pthread_mutex_unlock(philo->par->death);
	return (0);
}

void	*thread_routine(void *job)
{
	t_philo	*p;

	p = (t_philo *)job;
	while (!p->par->ready)
		continue ;
	if (p->id & 1)
		ft_usleep(p->par->time_to_eat * 0.9 + 1);
	while (!p->par->end)
	{
		ft_eat(p);
		ft_sleep_and_think(p);
	}
	return (NULL);
}
