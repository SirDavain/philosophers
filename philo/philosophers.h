/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:42:18 by dulrich           #+#    #+#             */
/*   Updated: 2024/10/06 07:59:54 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>

# define MAX_PHILOS 200

typedef struct s_philo
{
	int				*is_dead;
	int				id;
	int				is_eating;
	int				meals_eaten;
	int				nbr_of_philos;
	int				nbr_of_meals;
	size_t			start_time;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_t		threads;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*write_lock;
}	t_philo;

typedef struct s_data
{
	int				is_dead;
	t_philo			*philos;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
}	t_data;

//main.c
int		philo_is_dead(t_philo *philo);
void	create_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks);
int		main(int argc, char **argv);

//routine.c
void	*monitor_routine(void *ptr);
void	eating(t_philo *philos);
void	thinking(t_philo *philos);
void	sleeping(t_philo *philos);
void	*philo_routine(void *ptr);

//utils.c
int		ft_atoi(char *s);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
void	quit_philos(char *str, t_data *data, pthread_mutex_t *forks);
void	print_status(char *str, t_philo *philo, int id);

//check.c
int		death_flag_checker(t_philo *philos);
int		check_if_dead(t_philo *philo, size_t time_to_die);
int		check_if_all_ate(t_philo *philos);
int		check_arg_nbrs(char *str);
int		args_error(char **argv, t_philo *philos);

//init.c
int		create_threads(t_data *data, pthread_mutex_t *forks);
void	init_forks(pthread_mutex_t *forks, t_philo *philos);
void	init_program(t_data *data);

#endif
