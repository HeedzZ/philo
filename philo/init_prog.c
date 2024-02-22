/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:45:03 by marvin            #+#    #+#             */
/*   Updated: 2024/01/09 16:45:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}

void	init_forks(pthread_mutex_t *forks, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

static void	init_args(t_philo *philos, char **argv)
{
	philos->nb_philos = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	philos->hungry = 1;
	philos->meals_eaten = 0;
	philos->start_time = get_current_time();
	philos->last_meal = get_current_time();
	if (argv[5])
		philos->num_times_to_eat = ft_atoi(argv[5]);
	else
		philos->num_times_to_eat = -1;
}

void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
				char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].id = i + 1;
		init_args(&philos[i], argv);
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->dead_flag;
		if (philos[i].id % 2 == 0)
		{
			philos[i].r_fork = i;
			philos[i].l_fork = ((i + 1) % philos[i].nb_philos);
		}
		else
		{
			philos[i].r_fork = ((i + 1) % philos[i].nb_philos);
			philos[i].l_fork = i;
		}
		philos[i].forks = forks;
		i++;
	}
}
