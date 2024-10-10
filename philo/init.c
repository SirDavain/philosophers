/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:56:20 by dulrich           #+#    #+#             */
/*   Updated: 2024/10/10 07:23:25 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	monitor;
	int			i;

	if (pthread_create(&monitor, NULL, &monitor_routine, data->philos) != 0)
		return (1);
	i = -1;
	while (++i < data->philos[0].nbr_of_philos)
	{
		if (pthread_create(&data->philos[i].threads, NULL, &philo_routine,
				&data->philos[i]) != 0)
			return (1);
	}
	i = -1;
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	while (++i < data->philos[0].nbr_of_philos)
	{
		if (pthread_join(data->philos[i].threads, NULL) != 0)
			return (1);
	}
	return (0);
}

void	init_philo_input(t_philo *philos, char **argv)
{
	philos->nbr_of_philos = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philos->nbr_of_meals = ft_atoi(argv[5]);
	else
		philos->nbr_of_meals = -42;
}

void	create_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks,
						char **argv)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		philos[i].id = i + 1;
		init_philo_input(&philos[i], argv);
		philos[i].meals_eaten = 0;
		philos[i].is_eating = FALSE;
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].dead_lock = &data->dead_lock;
		philos[i].meal_lock = &data->meal_lock;
		philos[i].write_lock = &data->write_lock;
		philos[i].is_dead = &data->is_dead;
		philos[i].r_fork = &forks[i];
		if (i == 0)
			philos[i].l_fork = &forks[philos->nbr_of_philos - 1];
		else
			philos[i].l_fork = &forks[i - 1];
	}
}

void	ft_init(t_data *data, t_philo *philos, pthread_mutex_t *forks,
				char **argv)
{
	int	i;

	data->philos = philos;
	data->is_dead = 0;
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	i = -1;
	while (++i < ft_atoi(argv[1]))
		pthread_mutex_init(&forks[i], NULL);
}
