/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymostows <ymostows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:56:21 by ymostows          #+#    #+#             */
/*   Updated: 2024/01/10 14:56:21 by ymostows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_arg_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	check_valid_args(char **argv)
{
	if (ft_atoi(argv[1]) > MAX_PHILO || ft_atoi(argv[1]) <= 0
		|| check_arg_content(argv[1]) == 1)
		return (printf("Error : Invalid philosophers number\n"));
	if (ft_atoi(argv[2]) <= 0 || check_arg_content(argv[2]) == 1)
		return (printf("Error : Invalid time to die\n"));
	if (ft_atoi(argv[3]) <= 0 || check_arg_content(argv[3]) == 1)
		return (printf("Error : Invalid time to eat\n"));
	if (ft_atoi(argv[4]) <= 0 || check_arg_content(argv[4]) == 1)
		return (printf("Error : Invalid time to sleep\n"));
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_arg_content(argv[5]) == 1))
		return (printf(
				"Error : Invalid number of times each philosopher must eat\n"));
	return (0);
}

int	main(int argc, char *argv[])
{
	t_program		program;
	t_philo			philos[MAX_PHILO];
	pthread_mutex_t	*forks;

	if (argc == 5 || argc == 6)
	{
		if (check_valid_args(argv) > 0)
			return (1);
		forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
		if (!forks)
			return (0);
		init_program(&program, philos);
		init_forks(forks, ft_atoi(argv[1]));
		init_philos(philos, &program, forks, argv);
		create_threads(&program, forks);
		destr_all(NULL, &program, forks);
	}
	return (0);
}
