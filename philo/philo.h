/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:11:54 by achivela          #+#    #+#             */
/*   Updated: 2024/09/23 10:11:56 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int				time_last_meal;
	int				stamina;
	t_params		*par;
	struct timeval	time_born;
}	t_philo;

void		init_params(t_params *params, int argc, char **argv);
void		init_philo(t_philo *philo, t_params *params, int id);
int			ft_atoi(const char *str);
int			get_elapsed_time(struct timeval ta);
void		ft_usleep(t_philo *philo, int time);
void		ft_printf_status(t_philo *philo, char c);
void		check_forks(t_philo *philo);
void		ft_eat(t_philo *philo);
int			ft_die(t_philo *philo);
void		case_one_philo(t_philo *ph);
int			destroy_my_mutex(t_params *params);
int			check_args(int argc, char **argv);
#endif
