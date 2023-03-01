/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chales <chales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:20:41 by chales            #+#    #+#             */
/*   Updated: 2023/03/01 20:29:23 by chales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

void	sender(char c, pid_t pid)
{
	int	i;

	i = 0;
	while (i <= 7)
	{
		if (c & (1 << i))
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_printf("Error!\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_printf("Error!\n");			
				exit(EXIT_FAILURE);
			}
		}
		i++;
		usleep(200);
	}
}

int main(int ac, char	*av[])
{
	pid_t	pid;
	int		count;
	
	count = 0;
	if (ac == 3)
	{	
		pid = ft_atoi(av[1]);
		while (av[2] && av[2][count] != '\0')
		{
			sender(av[2][count], pid);
			++count;
		}
	}
	else
	{
		ft_printf("Usage : ./client <pid> <msg>\n");
		exit(EXIT_FAILURE);
	}
}
