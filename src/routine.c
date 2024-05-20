/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 09:05:27 by dulrich           #+#    #+#             */
/*   Updated: 2024/05/20 18:21:07 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_routine(void *ptr)
{
	t_philo	*philos;

	philos = (t_philo *)ptr;
	while (TRUE)
	{
		if (philo_is_dead(philos) || check_if_all_ate(philos))
			break ;
	}
	return (ptr);
}

void	eating(t_philo *philos)
{
	pthread_mutex_lock(philos->r_fork);
	print_status("took a fork", philos, philos->id);
	if (philos->nbr_of_philos == 1)
	{
		ft_usleep(philos->time_to_die);
		pthread_mutex_unlock(philos->r_fork);
		return ;
	}
	pthread_mutex_lock(philos->l_fork);
	print_status("took a fork", philos, philos->id);
	philos->is_eating = TRUE;
	print_status("is eating", philos, philos->id);
	pthread_mutex_lock(philos->meal_lock);
	philos->meals_eaten++;
	philos->last_meal = get_current_time();
	pthread_mutex_unlock(philos->meal_lock);
	ft_usleep(philos->time_to_eat);
	philos->is_eating = FALSE;
	pthread_mutex_unlock(philos->r_fork);
	pthread_mutex_unlock(philos->l_fork);
}

void	thinking(t_philo *philos)
{
	print_state("is thinking", philos, philos->id);
}

void	sleeping(t_philo *philos)
{
	print_state("is sleeping", philos, philos->id);
	ft_usleep(philos->time_to_sleep);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (void *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!death_flag_checker(philo)) 
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (ptr);
}
