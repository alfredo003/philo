/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:49:01 by achivela          #+#    #+#             */
/*   Updated: 2024/09/19 11:49:17 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	main(int argc, char **argv)
{
	t_params	params;

	if (argc == 5 || argc == 6)
	{
		if (init_params(&params, argv))
			return (put_error("Error: invalid arguments\n", &params, 0, 1));
		if (philos(&params))
			return (-1);
	}
	return (0);
}
