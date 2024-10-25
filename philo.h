/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:46:00 by achivela          #+#    #+#             */
/*   Updated: 2024/10/25 17:02:56 by achivela         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

# ifndef PHILO_H 
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define LFORK "has taken left fork"
# define RFORK "has taken right fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "\e[0;31mDIED\e[m"
# define LEFT 0
# define RIGHT 1

typedef struct s_params
{
	int				n_philo;
	int				ready;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				max_iter;
	int				check_meal;
	int				philos_full;
	int				over;
	long int		start;
	pthread_mutex_t	*meal_mtx;
	pthread_mutex_t	*ready_mtx;
	pthread_mutex_t	*over_mtx;
	pthread_mutex_t	*fork;
}	t_params;

/*
					id				= identification/index
					dead			= is dead
					iter_num		= number of iterations
					monitor_start	= 
					meal			= meals eaten
					life_tid		= life thread id
					lf				= left fork
					rf				= right fork
					par				= parameters
*/
typedef struct s_philo
{
	int				id;
	int				dead;
	int				iter_num;
	long int		monitor_start;
	long int		meal;
	pthread_t		life_tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_params		*params;
}	t_philo;


int			init_params(t_params *params, int ac, char **av);
int			init_monitor(t_params *par, t_philo *philo);
int			init_philo(t_params *params, t_philo *philo);
int			ft_atoi(const char *str);
void		end_monitor(t_params *par, t_philo *philo);
int			put_msg(char *s, t_params *params, t_philo *p, int malloc);
void		*philo_routine(void *job);
void		final_print(int alive);
int			monitoring(t_params *p);
void		check_monitor(t_params *par, t_philo *philo);
void		print_routine(t_philo *p, char *action);
int			ft_usleep(long int time);
long int	time_now(void);

#endif
