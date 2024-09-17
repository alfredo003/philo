#ifndef PHILO_H
#define PHILO_H
#include<stdio.h>
#include<stdlib.h>
#include <limits.h>

typedef struct s_params
{
	int				num;
	int				ready;
	int				t2d;
	int				t2e;
	int				t2s;
	int				max_iter;
	int				check_meal;
	int				over;
	long int		start;
	pthread_mutex_t	*death;
	pthread_mutex_t	*fork;
}	t_params;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				iter_num;
	long int		thread_start;
	long int		meal;
	pthread_t		life_tid;
	pthread_mutex_t	*lf;
	pthread_mutex_t	*rf;
	t_params		*par;
}	t_philo;

void	put_error(char *s, t_params *par, t_philo *p, int malloc);
int	ft_atoi(const char *str);
#endif
