/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 09:28:15 by dulrich           #+#    #+#             */
/*   Updated: 2024/10/08 07:31:43 by dulrich          ###   ########.fr       */
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
	while ((s[i] >= 9) && (s[i] <= 13 || s[i] == 32))
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
		return printf("Error: gettimeofday()\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	quit_philos(char *str, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	if (str != NULL)
		printf("%s \n", str);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	i = 0;
	while (i < data->philos[0].nbr_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	print_status(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!death_flag_checker(philo))
		printf("%zu %d %s \n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}
