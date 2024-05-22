/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:10:40 by dulrich           #+#    #+#             */
/*   Updated: 2024/05/22 15:42:40 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	done_eating;

	if (philos[0].nbr_of_meals == -1)
		return (0);
	i = 0;
	done_eating = 0;
	while (i < philos[0].nbr_of_philos)
	{
		pthread_mutex_lock(philos->meal_lock);
		if (philos[i].meals_eaten >= philos[i].nbr_of_meals)
			done_eating++;
		pthread_mutex_unlock(philos->meal_lock);
		i++;
	}
	if (done_eating == philos[0].nbr_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->is_dead = TRUE;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

int	check_if_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if ((get_current_time() - philo->last_meal >= time_to_die) \
		&& (philo->is_eating == FALSE))
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	death_flag_checker(t_philo *philos)
{
	pthread_mutex_lock(philos->dead_lock);
	if (philos->is_dead)
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
		if (str[i] < '0' || str[i] > '9')
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
		philos->nbr_of_meals = ft_atoi(argv[5]);
	if (!argv[5])
		philos->nbr_of_meals = -1;
	return (0);
}
