/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:10:40 by dulrich           #+#    #+#             */
/*   Updated: 2024/10/09 15:12:44 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	done_eating;

	if (philos[0].nbr_of_meals == -42)
		return (0);
	i = -1;
	done_eating = 0;
	while (++i < philos[0].nbr_of_philos)
	{
		pthread_mutex_lock(philos->meal_lock);
		if (philos[i].meals_eaten >= philos[i].nbr_of_meals)
			done_eating++;
		pthread_mutex_unlock(philos->meal_lock);
	}
	if (done_eating == philos[0].nbr_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->is_dead = true;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

int	check_if_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	printf("Is it time to die? %lu\n", get_current_time() - philo->last_meal);
	if ((get_current_time() - philo->last_meal >= time_to_die)
		&& (philo->is_eating == false))
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	return (pthread_mutex_unlock(philo->meal_lock), 0);
}

int	death_flag_checker(t_philo *philos)
{
	pthread_mutex_lock(philos->dead_lock);
	if (philos->is_dead)
	{
		printf("is dead\n");
		return (pthread_mutex_unlock(philos->dead_lock), 1);
	}
	return (pthread_mutex_unlock(philos->dead_lock), 0);
}

int	is_valid_nbr(char *str)
{
	int		i;
	long	n;

	n = ft_atoi(str);
	if (n > INT_MAX)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	args_error(char **argv, t_philo *philos)
{
	if (ft_atoi(argv[1]) > MAX_PHILOS || ft_atoi(argv[1]) <= 0
		|| !is_valid_nbr(argv[1]))
		return (1);
	if (ft_atoi(argv[2]) <= 0 || !is_valid_nbr(argv[2]))
		return (1);
	if (ft_atoi(argv[3]) <= 0 || !is_valid_nbr(argv[3]))
		return (1);
	if (ft_atoi(argv[4]) <= 0 || !is_valid_nbr(argv[4]))
		return (1);
	if (argv[5])
	{
		if (ft_atoi(argv[5]) <= 0 || !is_valid_nbr(argv[5]))
			return (1);
	}
	return (0);
}
