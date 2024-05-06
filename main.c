/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:41:33 by dulrich           #+#    #+#             */
/*   Updated: 2024/05/06 16:52:25 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_philos(t_philo philos)
{
	int	i;
	pthread_t	var;

	i = 1;
	while (i <= philos.nbr_of_philos)
	{
		/*create philo-threads
		pthread_create 
		*/
	}
}

void	is_eating()
{
	/* 
	if philo n is eating, philo n+1 and philo n-1 can't
	have a waiter who checks who is currently eating
	 */
}

void	init_program(t_philo philos, char *nbr_of_philos)
{
	philos.is_dead_flag = FALSE;
	philos.nbr_of_philos = ft_atoi(nbr_of_philos);
	pthread_mutex_init(&)
}

void	ft_usleep()
{
	
}

void	state_change()
{
	
}

void	philo_loop(t_data philos)
{
	while(!philos.is_dead_flag)
		run_philo_routine();
		if (all_meals_finished)
			return ;
	if (philos.is_dead_flag)
		return (printf())
}

void	thinking(t_philo philos)
{
	printf("%d is thinking", philos.id);
}

void	sleeping(t_philo philos)
{
	// use ft_usleep(philos.) to let them sleep for the amount of time inputted
	printf("%d is sleeping", philos.id);
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
int	check_args(char **argv, t_philo philos)
{
	if (ft_atoi(argv[1]) > MAX_PHILOS || ft_atoi(argv[1]) <= 0 || \
		check_arg_nbrs(argv[1]) == 1)
		return (printf("Invalid number of philosophers."), 1);
	else
		philos.nbr_of_philos = ft_atoi(argv[1]);
	if (ft_atoi(argv[2]) <= 0 || check_arg_nbrs(argv[2]) == 1)
		return (printf("Invalid time to die."), 1);
	else
		philos.time_to_die = ft_atoi(argv[2]);
	if (ft_atoi(argv[3]) <= 0 || check_arg_nbrs(argv[3]) == 1)
		return (printf("Invalid time to eat."), 1);
	else
		philos.time_to_eat = ft_atoi(argv[3]);
	if (ft_atoi(argv[4]) <= 0 || check_arg_nbrs(argv[4]) == 1)
		return (printf("Invalid time to sleep."), 1);
	else
		philos.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] && (ft_atoi(argv[5]) <= 0 || check_arg_nbrs(argv[5]) == 1))
		return (printf("Invalid nbr of times each philosopher must eat."), 1);
	else if (argv[5] && !(ft_atoi(argv[5]) <= 0 || check_arg_nbrs(argv[5]) == 1))
		philos.max_nbr_of_meals = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_philo	philos;
	t_data	data;
	pthread_mutex_t forks[MAX_PHILOS];
	
	if (argc != 5 || argc != 6)
		return (1);
	if (check_args(argv, philos) == 1)
		return (1);
	init_program(philos, argv[1]);
	create_philos(philos);
	philo_loop(data);
	return (0);
}