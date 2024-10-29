 #ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_params
{
	pthread_t		*threads;
	pthread_mutex_t	init_mutex;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	g_print_mutex;
	int				n_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				died;
	int				ac;
	char			**av;
}					t_params;

typedef struct s_philo
{
	int				id;
	int				num_ref;
	int				t_last_meal;
	int				stamina;
	struct timeval	t_born;
	t_params			*par;
}					t_philo;

void		init_params(t_params *params, int argc, char **argv);
void		init_philo(t_philo *philo, t_params *params, int id);
int			ft_atoi(const char *str);
int			get_elapsed_time_ms(struct timeval ta);
void		ft_usleep(t_philo *philo, int time);
void		ft_printf_status(t_philo *philo, char c);
void		check_forks(t_philo *philo);
void		ft_eat(t_philo *philo);
int			ft_die(t_philo *philo);
void		caseof1(t_philo *ph);
int			destroy_my_mutex(t_params *params);
int	check_args(int argc, char **argv);
#endif
