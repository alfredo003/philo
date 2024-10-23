/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:54:16 by achivela          #+#    #+#             */
/*   Updated: 2024/10/23 12:28:51 by achivela         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_params	params;

	if (argc == 5 || argc == 6)
	{
		if (init_params(&params, argv))
			return (put_error("Error: invalid arguments\n", &params, 0, 1));
		if (philos(&params))
			return (1);
	}
	//else
		//put_error("./philo [num_of_philo] [time_die] [time_eat] [time_sleep]\n",&params, 0, 0);
	return (0);
}
