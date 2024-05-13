/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:56:20 by dulrich           #+#    #+#             */
/*   Updated: 2024/05/13 16:05:45 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 1;
	while (i <= philos->nbr_of_philos)
	{
		philos[i].id = i;
		philos[i].meals_eaten = 0;
		philos[i].is_eating = FALSE;
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].dead_lock = &data->dead_lock;
		philos[i].meal_lock = &data->meal_lock;
		philos[i].write_lock = &data->write_lock;
		philos[i].is_dead = &data->is_dead_flag;
		philos[i].r_fork = &forks[i];
		if (i == 1)
			philos[i].l_fork = &forks[philos[i].nbr_of_philos - 1];
		else
			philos[i].l_fork = &forks[i - 1];
		i++;
	}
}

int	init_threads(t_data *data, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	observer;

	if (pthread_create(&observer, NULL, &monitor_routine, data->philos) != 0)
		terminate_program("Error: Thread creation", data, forks);
	i = 0;
	while (i < data->philos[0].nbr_of_philos)
	{
		if (pthread_create(&data->philos[i], NULL, &philo_routine, \
			&data->philos[i]) != 0)
			terminate_program("Error: Thread creation", data, forks);
		i++;
	}
	if (pthread_join(observer, NULL) != 0)
		terminate_program("Error: Thread joining", data, forks);
	i = 0;
	while (i < data->philos[0].nbr_of_philos)
	{
		if (pthread_join(data->philos[i].threads, NULL) != 0)
			terminate_program("Error: Thread joining", data, forks);
		i++;
	}
	return (0);
}

void	init_forks(pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->nbr_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_data *data)
{
	data->is_dead_flag = FALSE;
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
}
