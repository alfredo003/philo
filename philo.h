#ifndef PHILO_H
#define PHILO_H
#include<stdio.h>
#include<stdlib.h> 

typedef struct s_params
{
	int				number_of_philosophers;
	int				ready;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_iter;
	int				check_n_snack;
	int				end;
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

int	put_error(char *s, t_params *par, t_philo *p, int malloc);
int	ft_atoi(const char *str);
int	start_params(t_params *params, char **argv);
#endif
