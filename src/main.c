/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:41:33 by dulrich           #+#    #+#             */
/*   Updated: 2024/05/19 09:06:07 by dulrich          ###   ########.fr       */
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
			print_state("dead", &philo[i], philo[i].id);
			pthread_mutex_lock(&philo->dead_lock);
			*philo->is_dead = TRUE;
			pthread_mutex_unlock(&philo->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philos[MAX_PHILOS];
	t_data	data;
	pthread_mutex_t forks[MAX_PHILOS];
	
	if (argc != 5 || argc != 6)
		return (1);
	if (check_args(argv, &philos) == 1)
		return (1);
	init_program(&data);
	init_forks(forks, &philos);
	create_philos(philos, &data, forks);
	init_threads(&data, forks);
	terminate_program("Successful completion", &data, forks);
	return (0);
}
