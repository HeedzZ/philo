/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:09:16 by marvin            #+#    #+#             */
/*   Updated: 2024/01/09 16:09:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define MAX_PHILO 250

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				nb_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

void	init_program(t_program *program, t_philo *philos);
void	init_forks(pthread_mutex_t *forks, int nb_philo);
void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
			char **argv);
int		ft_atoi(char *str);
int		ft_msleep(size_t millisec);
size_t	get_current_time(void);
void	free_forks(pthread_mutex_t *forks, int nb_philos);
void	print_msg(char *str, t_philo *philo, int id);
int		dead_notif(t_philo *philo);
int		destr_all(char *str, t_program *program, pthread_mutex_t *forks);
int		create_threads(t_program *program, pthread_mutex_t *forks);
void	*monitor(void *p);
void	eat(t_philo *philo);
void	action_sleep(t_philo *philo);
void	think(t_philo *philo);
#endif