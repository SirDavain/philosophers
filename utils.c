/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 09:28:15 by dulrich           #+#    #+#             */
/*   Updated: 2024/05/08 15:07:47 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Error: gettimeofday()\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time - start) < milliseconds)
		usleep(500);
	return (0);
}

void	stop_program(t_philo *philos, t_data *data)
{
	
}
