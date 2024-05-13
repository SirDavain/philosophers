/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:41:33 by dulrich           #+#    #+#             */
/*   Updated: 2024/05/12 19:28:40 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 1;
	while (i <= philos->nbr_of_philos)
	{
		philos[i].id = i;
		philos[i].meals_eaten = 0;
		philos[i].eating = FALSE;
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].dead_lock = &data->dead_lock;
		philos[i].meal_lock = &data->meal_lock;
		philos[i].write_lock = &data->write_lock;
		philos[i].is_dead = &data->is_dead_flag;
		philos[i].r_fork = &forks[i];
		if (i == 1)
			philos[i].l_fork = &forks[philos[i].nbr_of_philos - 1];
		else
			philos[i].l_fork = &forks[i - 1];
		i++;
	}
}

int	init_threads(t_data *data, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	observer;

	if (pthread_create(&observer, NULL, &monitor_routine, data->philos) != 0)
		terminate_program("Thread creation", data, forks);
	i = 0;
	while (i < data->philos[0].nbr_of_philos)
	{
		if (pthread_create(&data->philos[i], NULL, &philo_routine, &data->philos[i]) != 0)
			terminate_program("Thread creation", data, forks);
		i++;
	}
}

void	eating(t_philo *philos)
{
	/* 
	- if philo n is eating, philo n+1 and philo n-1 can't
	- have a waiter/monitor, who checks who is currently eating
	 */
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

void	init_forks(pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->nbr_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_data *data)
{
	data->is_dead_flag = FALSE;
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
}

/* void	philo_loop(t_data philos)
{
	while(!philos.is_dead_flag)
		run_philo_routine();
		if (all_meals_finished)
			return ;
	if (philos.is_dead_flag)
		return (printf())
} */

int	death_checker(t_philo *philos)
{
	pthread_mutex_lock(philos->dead_lock);
	if (philos->is_dead == 1)
		return (pthread_mutex_unlock(philos->dead_lock), 1);
	thread_mutex_unlock(philos->dead_lock);
	return (0);
}

void	thinking(t_philo *philos)
{
	printf("%d is thinking", philos.id);
}

void	sleeping(t_philo *philos)
{
	// use ft_usleep(philos.) to let them sleep for the amount of time inputted
	printf("%d is sleeping", philos.id);
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
	philo_loop(&data);
	return (0);
}