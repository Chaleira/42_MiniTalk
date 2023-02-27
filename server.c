/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chales <chales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:39:03 by chales            #+#    #+#             */
/*   Updated: 2023/02/27 18:29:06 by chales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"

void	handler(int signal)
{
	static	int		i;
	static	char	c;

	if (i == 8)
	{
		write (1, &c, 1);
		i = 0;
		c = 0;
	}
	
	if (signal == SIGUSR1)
	{
		ft_printf("1\n");
		c |= (1 << i);
		i++;
	}
	else if (signal == SIGUSR2)
	{
		ft_printf("0\n");
		c |= (0 << i);
		i++;
	}
}

int	main(void)
{
	pid_t	pid;
	
	pid = getpid();
	ft_printf("PID : %d\n", pid);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
	{
		pause();
	}
	return (0);
}
