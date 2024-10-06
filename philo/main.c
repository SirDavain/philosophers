/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:41:33 by dulrich           #+#    #+#             */
/*   Updated: 2024/10/06 07:59:49 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_is_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].nbr_of_philos)
	{
		if (check_if_dead(&philo[i], philo[i].time_to_die))
		{
			print_status("is dead", &philo[i], philo[i].id);
			pthread_mutex_lock(philo[0].dead_lock);
			*philo->is_dead = true;
			pthread_mutex_unlock(philo[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	create_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (++i <= philos->nbr_of_philos)
	{
		philos[i].id = i;
		philos[i].meals_eaten = 0;
		philos[i].is_eating = false;
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].dead_lock = &data->dead_lock;
		philos[i].meal_lock = &data->meal_lock;
		philos[i].write_lock = &data->write_lock;
		philos[i].is_dead = &data->is_dead;
		philos[i].r_fork = &forks[i];
		if (i == 1)
			philos[i].l_fork = &forks[philos[i].nbr_of_philos - 1];
		else
			philos[i].l_fork = &forks[i - 1];
	}
}

int	main(int argc, char **argv)
{
	t_philo			philos[MAX_PHILOS];
	t_data			data;
	pthread_mutex_t	forks[MAX_PHILOS];

	if (argc != 5 && argc != 6)
		return (printf("Not the right amount of arguments.\n"), 1);
	if (args_error(argv, philos))
		return (1);
	init_program(&data);
	init_forks(forks, philos);
	create_philos(philos, &data, forks);
	create_threads(&data, forks);
	quit_philos("Everyone survived", &data, forks);
	return (0);
}
