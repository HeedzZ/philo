/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:09:51 by marvin            #+#    #+#             */
/*   Updated: 2024/01/17 15:09:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destr_mutex(t_program *program)
{
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
}

static void	destr_forks(pthread_mutex_t *forks, int nb_philos)
{
	int	i;

	i = 0;
	while (i < nb_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	destr_all(char *str, t_program *program, pthread_mutex_t *forks)
{
	if (str)
		printf("%s\n", str);
	destr_mutex(program);
	destr_forks(forks, program->philos[0].nb_philos);
	free(forks);
	return (1);
}
