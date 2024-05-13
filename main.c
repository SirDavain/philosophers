/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:41:33 by dulrich           #+#    #+#             */
/*   Updated: 2024/05/13 16:03:48 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_if_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die \
		&& philo->eating == 0)
		return (pthread_mutex_unlock(&philo->meal_lock), 1);
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

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

int	check_if_all_ate()
{
	
}

void	*monitor_routine(void *ptr)
{
	t_philo	*philos;

	philos = (t_philo *)ptr;
	while (TRUE)
	{
		if (philo_is_dead(philos) || check_if_all_ate())
			break ;
	}
	return (ptr);
}

void	eating(t_philo *philos)
{
	
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
	while (!death_checker(philo)) 
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (ptr);
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