/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:41:33 by dulrich           #+#    #+#             */
/*   Updated: 2024/03/12 12:47:22 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_philos()
{
	
}

int	ft_atoi(char *s)
{
	int	i;
	int	nbr;
	
	i = 0;
	nbr = 0;
	while (s[i] >= 9 && s[i] <= 13 || s[i] == 32)
		i++;
	if (s[i] == '-')
		return (-1);
	while (s[i] >= '0' && s[i] <= '9')
	{
		nbr *= 10;
		nbr += s[i++] - 48;
	}
	return (nbr);
}

int	main(int argc, char **argv)
{
	int	philos;
	
	if (argc != 5 || argc != 6)
		return (1);
	philos = ft_atoi(argv[1]);
	if (philos == -1)
		return (NULL);
	
}