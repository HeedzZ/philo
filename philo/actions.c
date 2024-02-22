/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:06:01 by marvin            #+#    #+#             */
/*   Updated: 2024/01/17 18:06:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	print_msg("is thinking", philo, philo->id);
}

void	action_sleep(t_philo *philo)
{
	print_msg("is sleeping", philo, philo->id);
	ft_msleep(philo->time_to_sleep);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->r_fork]);
	print_msg("has taken a fork", philo, philo->id);
	if (philo->nb_philos == 1)
	{
		ft_msleep(philo->time_to_die);
		pthread_mutex_unlock(&philo->forks[philo->r_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->forks[philo->l_fork]);
	print_msg("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	print_msg("is eating", philo, philo->id);
	ft_msleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->forks[philo->r_fork]);
}
