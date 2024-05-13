/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:10:40 by dulrich           #+#    #+#             */
/*   Updated: 2024/05/13 14:54:30 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_checker(t_philo *philos)
{
	pthread_mutex_lock(philos->dead_lock);
	if (philos->is_dead == 1)
		return (pthread_mutex_unlock(philos->dead_lock), 1);
	pthread_mutex_unlock(philos->dead_lock);
	return (0);
}

int	check_arg_nbrs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[1] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_args(char **argv, t_philo *philos)
{
	if (ft_atoi(argv[1]) > MAX_PHILOS || ft_atoi(argv[1]) <= 0 || \
		check_arg_nbrs(argv[1]) == 1)
		return (printf("Invalid number of philosophers."), 1);
	philos->nbr_of_philos = ft_atoi(argv[1]);
	if (ft_atoi(argv[2]) <= 0 || check_arg_nbrs(argv[2]) == 1)
		return (printf("Invalid time to die."), 1);
	philos->time_to_die = ft_atoi(argv[2]);
	if (ft_atoi(argv[3]) <= 0 || check_arg_nbrs(argv[3]) == 1)
		return (printf("Invalid time to eat."), 1);
	philos->time_to_eat = ft_atoi(argv[3]);
	if (ft_atoi(argv[4]) <= 0 || check_arg_nbrs(argv[4]) == 1)
		return (printf("Invalid time to sleep."), 1);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] && (ft_atoi(argv[5]) <= 0 || check_arg_nbrs(argv[5]) == 1))
		return (printf("Invalid nbr of times each philosopher must eat."), 1);
	if (argv[5] && !(ft_atoi(argv[5]) <= 0 || check_arg_nbrs(argv[5]) == 1))
		philos->max_nbr_of_meals = ft_atoi(argv[5]);
}
