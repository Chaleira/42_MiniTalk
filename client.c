/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chales <chales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:20:41 by chales            #+#    #+#             */
/*   Updated: 2023/02/28 16:58:05 by chales           ###   ########.fr       */
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

	i = 7;
	while (i >= 0)
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
		i--;
	}
}

int main(int ac, char	*av[])
{
	pid_t	pid;
	int		j;
	char	*str;
	
	j = 0;
	if (ac != 3)
		return (0);
	pid = ft_atoi(av[1]);
	str = ft_strdup(av[2]);
	while (str && str[j] != '\0')
	{
		sender(str[j], pid);
		j++;
	}
	return (0);
}
