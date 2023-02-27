/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chales <chales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:20:41 by chales            #+#    #+#             */
/*   Updated: 2023/02/27 18:01:08 by chales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

void	sender(char c, pid_t pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c & i) == 1)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_printf("Error!\n");
				return ;
			}
		}
		else if ((c & i) == 0)
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_printf("Error!\n");			
				return ;
			}
		}
		i++;
		usleep(500);
	}
}

int main(int ac, char	*av[])
{
	pid_t	pid;
	int		i;

	i = 0;
	if (ac != 3)
		return (0);
	pid = ft_atoi(av[1]);
	while (av[2][i] && av[2][i] != '\0')
	{
		sender(av[2][i], pid);
		i++;
	}
	return (0);
}
