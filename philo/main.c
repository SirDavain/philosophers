/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:41:33 by dulrich           #+#    #+#             */
/*   Updated: 2024/10/09 17:36:59 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_is_dead(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nbr_of_philos)
	{
		if (check_if_dead(&philo[i], philo[i].time_to_die))
		{
			print_status("is dead", &philo[i], philo[i].id);
			pthread_mutex_lock(philo->dead_lock);
			*philo->is_dead = 1;
			pthread_mutex_unlock(philo->dead_lock);
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];

	if (argc < 5 || argc > 6)
		return (printf("Error: Not the right amount of arguments.\n"), 1);
	if (args_error(argv, philos))
		return (printf("Error: Invalid argument found\n"), 1);
	ft_init(&data, philos, forks, argv);
	create_philos(philos, &data, forks, argv);
	if (create_threads(&data, forks) == 1)
		return (quit_philos("Thread error", &data, forks), 1);
	quit_philos("The meal is finished.", &data, forks);
	return (0);
}
