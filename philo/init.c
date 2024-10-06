/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:56:20 by dulrich           #+#    #+#             */
/*   Updated: 2024/10/06 08:00:07 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	monitor;
	int			i;

	if (pthread_create(&monitor, NULL, &monitor_routine, data->philos) != 0)
		quit_philos("Error: Thread creation", data, forks);
	i = -1;
	while (++i < data->philos->nbr_of_philos)
	{
		if (pthread_create(&data->philos[i].threads, NULL, &philo_routine, \
			&data->philos[i]) != 0)
			quit_philos("Error: Thread creation", data, forks);
	}
	if (pthread_join(monitor, NULL) != 0)
		quit_philos("Error: Thread joining", data, forks);
	i = -1;
	while (++i < data->philos->nbr_of_philos)
	{
		if (pthread_join(data->philos[i].threads, NULL) != 0)
			quit_philos("Error: Thread joining", data, forks);
	}
	return (0);
}

void	init_forks(pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->nbr_of_philos)
		pthread_mutex_init(&forks[i], NULL);
}

void	init_program(t_data *data)
{
	data->is_dead = false;
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
}
