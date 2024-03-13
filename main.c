/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:41:33 by dulrich           #+#    #+#             */
/*   Updated: 2024/03/13 14:53:44 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_philos(t_philos philo)
{
	int	i;
	pthread_t	var;

	i = 0;
	while (i < philos)
	{
		
	}
}

int	ft_atoi(char *s)
{
	int	i;
	int	nbr;
	int	sign;
	
	i = 0;
	nbr = 0;
	sign = 1;
	while (s[i] >= 9 && s[i] <= 13 || s[i] == 32)
		i++;
	if (s[i] == '-')
		sign = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		nbr *= 10;
		nbr += s[i++] - 48;
	}
	return (nbr * sign);
}

void	init_program(t_philo philo)
{
	philo.is_dead_flag = FALSE;
	
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

void	ft_usleep()
{
	
}

void	philo_loop(t_philo philo)
{
	while(!philo.is_dead_flag)
		run_philo_routine();
		if (all_meals_finished)
			return ;
}

int	check_args(char **argv)
{
	if (ft_atoi(argv[1]) > MAX_PHILOS || ft_atoi(argv[1]) <= 0 || \
		check_arg_nbrs(argv[1]) == 1)
		return (printf("Invalid number of philosophers."), 1);
	if (ft_atoi(argv[2]) <= 0 || check_arg_nbrs(argv[2]) == 1)
		return (printf("Invalid time to die."), 1);
	if (ft_atoi(argv[3]) <= 0 || check_arg_nbrs(argv[3]) == 1)
		return (printf("Invalid time to eat."), 1);
	if (ft_atoi(argv[4]) <= 0 || check_arg_nbrs(argv[4]) == 1)
		return (printf("Invalid time to sleep."), 1);
	if (argv[5] && (ft_atoi(argv[5]) <= 0 || check_arg_nbrs(argv[5]) == 1))
		return (printf("Invalid nbr of times each philosopher must eat."), 1);
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	
	if (argc != 5 || argc != 6)
		return (1);
	if (check_args(argv) == 1)
		return (1);
	init_program(philo);
	create_philos(philo);
	
}