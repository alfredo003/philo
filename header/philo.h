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
	int				t_die;
	int				t_eat;
	int				t_sleep;
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
	t_th			*th;
}					t_philo;

void		start_structs(t_th *th, int ac, char **av);
void		init_ph(t_ph *ph, t_th *th, int id);
int			ft_atoi(const char *str);
int			get_elapsed_time_ms(struct timeval ta);
void		ft_usleep(t_ph *ph, int time);
void		ft_printf_status(t_ph *ph, char c);
void		check_forks(t_ph *ph);
void		ft_eat(t_ph *ph);
int			ft_die(t_ph *ph);
void		caseof1(t_ph *ph);
int			destroy_my_mutex(t_th *th);
int			validate_args(int ac, char **av);
#endif
