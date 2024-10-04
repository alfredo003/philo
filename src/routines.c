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

void ft_sleep_and_think(t_philo *p)
{
	ft_usleep(p->par->time_to_sleep);
	print_logs(p,"is sleeping");
	print_logs(p,"is thinking");
}

void ft_eat(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	print_logs(p,"has taken a fork");
	pthread_mutex_lock(p->right_fork);
	print_logs(p,"has taken a fork");
	p->snack = time_now();
	ft_usleep(p->par->time_to_eat);
	print_logs(p,"is eating");
	p->iter_num++;
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}
void	*routine(void *task)
{
	t_philo	*p;

	p = (t_philo *)task;
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
