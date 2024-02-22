/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:40:18 by marvin            #+#    #+#             */
/*   Updated: 2024/01/17 16:40:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *p)
{
	t_philo			*philo ;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		ft_msleep((philo->time_to_eat));
	while (1)
	{
		if (ft_check_health(philo) == 0)
			return (0);
		eat(philo);
		if (ft_check_health(philo) == 0)
			return (0);
		action_sleep(philo);
		think(philo);
		usleep(200);
	}
	return (0);
}

int	create_threads(t_program *program, pthread_mutex_t *forks)
{
	int			i;
	int			nb_philos;

	nb_philos = program->philos[0].nb_philos;
	i = 0;
	while (i < nb_philos)
	{
		if (pthread_create(&program->philos[i].thread, 0, routine,
				&program->philos[i]) != 0)
			return (destr_all("Error : Thread creation error", program, forks));
		i++;
	}
	monitor(program->philos, 0, 0);
	i = 0;
	while (i < program->philos[0].nb_philos)
	{
		if (pthread_join(program->philos[i].thread, 0) != 0)
			return (destr_all("Error : Thread join error", program, forks));
		i++;
	}
	return (0);
}
