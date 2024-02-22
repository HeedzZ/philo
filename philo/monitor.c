/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:11:09 by marvin            #+#    #+#             */
/*   Updated: 2024/01/17 17:11:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_health(t_philo *philos)
{
	int	i;

	pthread_mutex_lock((philos[0].meal_lock));
	if (*philos[0].dead)
		i = 0;
	else
		i = 1;
	pthread_mutex_unlock((philos[0].meal_lock));
	return (i);
}

int	ft_check_vitals(t_philo *philos, int i)
{
	pthread_mutex_lock((philos->meal_lock));
	if ((get_current_time() - philos[i].last_meal)
		> (unsigned long)philos->time_to_die)
	{
		*philos[i].dead = 1;
		pthread_mutex_unlock((philos[i].meal_lock));
		print_msg("died", &philos[i], philos[i].id);
		return (1);
	}
	else if (philos[i].num_times_to_eat > 0 && philos[i].hungry == 1)
	{
		if (philos[i].meals_eaten >= philos[i].num_times_to_eat)
		{
			philos[i].hungry = 0;
			pthread_mutex_unlock((philos[i].meal_lock));
			return (2);
		}
		pthread_mutex_unlock((philos[i].meal_lock));
	}
	else
		pthread_mutex_unlock((philos[i].meal_lock));
	return (0);
}

void	monitor(t_philo *philos, int all_philos, int vitals)
{
	int	i;

	while (1)
	{
		i = 0;
		if (ft_check_health(philos) == 0)
			break ;
		while (i < philos[0].nb_philos)
		{
			vitals = ft_check_vitals(philos, i);
			if (vitals == 1)
				break ;
			else if (vitals == 2)
				all_philos++;
			if (all_philos == philos[0].nb_philos)
			{
				pthread_mutex_lock((philos[i].meal_lock));
				*philos[i].dead = 1;
				pthread_mutex_unlock((philos[i].meal_lock));
			}
			i++;
		}
		usleep(100);
	}
}
