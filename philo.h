#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_params
{
	int				n_philo;
	int				ready;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_iter;
	int				check_n_snack;
	int				end;
	long int		time_start;
	pthread_mutex_t	*death;
	pthread_mutex_t	*fork;
}	t_params;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				iter_num;
	long int		thread_start;
	long int		snack;
	pthread_t		life_tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_params		*params;
}	t_philo;

int			put_error(char *string, t_params *params, t_philo *p, int malloc);
int			ft_atoi(const char *str);
int			init_params(t_params *params, char **argv);
int	init_thread(t_params *params, t_philo *philo);
// int			ft_usleep(long int time);
// int			check_death(t_philo *philo);
// int			someone_died(t_philo *philo);
int			philos(t_params *params);
int			init_philo(t_params *params, t_philo *philo);
// int			check_snacks(t_philo params, int last);
// void		print_logs(t_philo *philo, char *action);
// void		*routine(void *job);
// long int	time_now(void);

#endif