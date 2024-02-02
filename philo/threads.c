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
		usleep(1);
	while (!dead_notif(philo))
	{
		eat(philo);
		action_sleep(philo);
		think(philo);
	}
	return (0);
}

int	create_threads(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	th_monitor;
	int			i;
	int			nb_philos;

	nb_philos = program->philos[0].nb_philos;
	if (pthread_create(&th_monitor, 0, &monitor, program->philos) != 0)
		return (destr_all("Error : Thread creation error", program, forks));
	i = 0;
	while (i < nb_philos)
	{
		if (pthread_create(&program->philos[i].thread, 0, routine,
				&program->philos[i]) != 0)
			return (destr_all("Error : Thread creation error", program, forks));
		i++;
	}
	if (pthread_join(th_monitor, 0) != 0)
		return (destr_all("Error : Thread join error", program, forks));
	i = 0;
	while (i < program->philos[0].nb_philos)
	{
		if (pthread_join(program->philos[i].thread, 0) != 0)
			return (destr_all("Error : Thread join error", program, forks));
		i++;
	}
	return (0);
}
