/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:41:33 by dulrich           #+#    #+#             */
/*   Updated: 2024/03/12 14:18:20 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_philos(int philos)
{
	int	i;
	pthread_t

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

void	ft_usleep()
{
	
}

int	check_args(char **argv)
{
	
}

int	main(int argc, char **argv)
{
	t_philos	philo;
	int			philos;
	
	
	if (argc != 5 || argc != 6)
		return (1);
	if (check_args(argv) == 1)
		return (1);
	init_struct();
	create_philos(philos);

	while(!dead_flag)
		run_philo_routine();
		if (all_meals_finished)
			return ;
}