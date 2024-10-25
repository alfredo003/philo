/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:49:01 by achivela          #+#    #+#             */
/*   Updated: 2024/10/25 18:05:10 by achivela         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_params	params;

	if (argc != 5 && argc != 6)
		return (put_msg("\033[0;41m./philo [num_philo] [time_die] [time_eat] [time_sleep]\n", 0, 0, 0));
	if (init_params(&params, argc, argv))
	{
		end_monitor(&params, NULL);
		return (EXIT_FAILURE);
	}
	if (monitoring(&params))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
