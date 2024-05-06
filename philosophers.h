/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:42:18 by dulrich           #+#    #+#             */
/*   Updated: 2024/05/06 16:35:16 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHERS_H
 #define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

# define MAX_PHILOS 200
# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	int		id;
	int		meals_eaten;
	size_t	nbr_of_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	max_nbr_of_meals;
	size_t	r_fork;
	size_t	l_fork;	
}				t_philo;

typedef struct s_data
{
	int				is_dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philos;
}				t_data;

//Functions


//Utils
int	ft_atoi(char *s);

#endif